#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#include <QMC5883LCompass.h>

const int MOTOR_PIN = 4;      
const int CE_PIN = 9;         
const int CSN_PIN = 10;       

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001"; 

MPU6050 mpu6050(Wire);
QMC5883LCompass compass;

struct PacketData {
  byte throttle; 
  bool armSwitch; 
  int droneX;     
  int droneY;     
  int droneZ;     
};
PacketData radioData;

unsigned long lastSignalTime = 0;
const unsigned long TIMEOUT_MS = 500; 
bool isArmed = false;

// --- PID Altitude Parameters ---
float Kp = 1.2;  
float Ki = 0.05; 
float Kd = 0.4;  

float error = 0, lastError = 0, integral = 0, derivative = 0;
unsigned long lastLoopTime = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0); 

  Wire.begin();
  
  // Initialize IMU
  mpu6050.begin();
  Serial.println("Calibrating IMU... Keep drone perfectly flat and still!");
  mpu6050.calcGyroOffsets(true); 

  // Initialize QMC5883P Magnetometer
  compass.init();
  // Optional: If your heading numbers feel distorted later, 
  // you will need to run the library's calibration sketch and insert your values here:
  // compass.setCalibration(minX, maxX, minY, maxY, minZ, maxZ);

  // Initialize Radio
  if (!radio.begin()) {
    while (1); 
  }
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); 
  radio.startListening();        
  
  lastLoopTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  float dt = (currentTime - lastLoopTime) / 1000.0; 

  mpu6050.update();
  
  // Read Magnetometer Heading (0 to 359 degrees)
  compass.read();
  int headingDegrees = compass.getAzimuth(); 
  if (headingDegrees < 0) {
    headingDegrees += 360; // Standardize to positive degrees
  }

  float currentRoll = mpu6050.getAngleX();
  float currentPitch = mpu6050.getAngleY();

  if (radio.available()) {
    radio.read(&radioData, sizeof(PacketData));
    lastSignalTime = currentTime; 
    
    if (radioData.armSwitch && radioData.throttle < 10 && radioData.droneX != -1) {
      isArmed = true; 
    } else if (!radioData.armSwitch || radioData.droneX == -1) {
      isArmed = false; 
      integral = 0; 
    }

    if (abs(currentRoll) > 45.0 || abs(currentPitch) > 45.0) {
      isArmed = false;
      Serial.println("SAFETY CRITICAL: TILT LIMIT EXCEEDED!");
    }

    if (isArmed && dt > 0) {
      float targetHeight = map(radioData.throttle, 0, 255, 50, 400);
      error = targetHeight - radioData.droneZ;

      integral += error * dt;
      integral = constrain(integral, -50, 50); 
      derivative = (error - lastError) / dt;

      float pidOutput = (Kp * error) + (Ki * integral) + (Kd * derivative);
      float hoverThrust = 100; 
      int finalMotorPWM = constrain(hoverThrust + pidOutput, 0, 255);

      analogWrite(MOTOR_PIN, finalMotorPWM);
      
      lastError = error;
      lastLoopTime = currentTime;

      Serial.print("Z: "); Serial.print(radioData.droneZ);
      Serial.print(" | Roll: "); Serial.print(currentRoll);
      Serial.print(" | Yaw (QMC): "); Serial.println(headingDegrees);
    } else {
      analogWrite(MOTOR_PIN, 0);
    }
  }

  if (millis() - lastSignalTime > TIMEOUT_MS) {
    isArmed = false;
    analogWrite(MOTOR_PIN, 0);
  }
}