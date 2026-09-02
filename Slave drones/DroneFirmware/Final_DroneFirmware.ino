#include <Wire.h>
#include <MPU6050_light.h>
#include <esp_now.h>
#include <WiFi.h>

MPU6050 mpu(Wire);

const int M0 = 3; // Motor 0 (Front Right / CCW usually)
const int M1 = 2; // Motor 1 (Front Left / CW usually)
const int M2 = 1; // Motor 2 (Back Right / CW usually)
const int M3 = 4; // Motor 3 (Back Left / CCW usually)

// ESP-NOW Data Structure
typedef struct struct_message {
  int16_t throttle;
} struct_message;

struct_message receivedData;
volatile int16_t currentThrottle = 0;

// ---------------------------------------------------------
// PID TUNING VARIABLES
// ---------------------------------------------------------
float kp = 1.2;
float ki = 0.0;
float kd = 0.4;

float rollError, rollIntegral, prevRollError;
float pitchError, pitchIntegral, prevPitchError;
unsigned long prevTime;

// ESP-NOW Receive Callback
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  currentThrottle = receivedData.throttle;
}

void setup() {
  Serial.begin(115200);
  delay(4000);
  Serial.println("\n========================================");
  Serial.println("[SYSTEM] ESP32-S3 Flight Controller Booting...");
  Serial.print("[SYSTEM] DRONE MAC ADDRESS: ");
  Serial.println(WiFi.macAddress());
  Serial.println("========================================\n");

  // Initialize Custom I2C Pins
  Wire.begin(11, 12);
  byte status = mpu.begin();
  Serial.print("[IMU] MPU6050 status: ");
  Serial.println(status);
  
  // Keep the drone perfectly still during boot for 3 seconds!
  Serial.println("[IMU] Calculating offsets, DO NOT MOVE DRONE!");
  delay(1000);
  mpu.calcOffsets(); 
  Serial.println("[IMU] Calibration Complete.");

  ledcAttach(M0, 5000, 10);
  ledcAttach(M1, 5000, 10);
  ledcAttach(M2, 5000, 10);
  ledcAttach(M3, 5000, 10);
  
  ledcWrite(M0, 0); ledcWrite(M1, 0); ledcWrite(M2, 0); ledcWrite(M3, 0);

  if (esp_now_init() == ESP_OK) {
    Serial.println("[ESP-NOW] Initialized Successfully.");
    esp_now_register_recv_cb(OnDataRecv);
  } else {
    Serial.println("[ESP-NOW] Initialization FAILED!");
  }

  prevTime = millis();
  Serial.println("[SYSTEM] Ready for Flight Loop.");
}

void loop() {
  mpu.update();

  // Calculate loop time (dt)
  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  if (dt <= 0) return;

  float actualRoll = mpu.getAngleY();
  float actualPitch = -mpu.getAngleX(); 

  rollError = 0 - actualRoll;
  rollIntegral += rollError * dt;
  float rollDerivative = (rollError - prevRollError) / dt;
  float rollPID = (kp * rollError) + (ki * rollIntegral) + (kd * rollDerivative);
  prevRollError = rollError;

  pitchError = 0 - actualPitch;
  pitchIntegral += pitchError * dt;
  float pitchDerivative = (pitchError - prevPitchError) / dt;
  float pitchPID = (kp * pitchError) + (ki * pitchIntegral) + (kd * pitchDerivative);
  prevPitchError = pitchError;

  int m0_val = currentThrottle + pitchPID + rollPID;
  int m1_val = currentThrottle - pitchPID + rollPID;
  int m2_val = currentThrottle + pitchPID - rollPID;
  int m3_val = currentThrottle - pitchPID - rollPID;

  if (currentThrottle < 20) {
    ledcWrite(M0, 0); 
    ledcWrite(M1, 0); 
    ledcWrite(M2, 0); 
    ledcWrite(M3, 0);

    rollIntegral = 0; 
    pitchIntegral = 0; 
  } else {
    ledcWrite(M0, constrain(m0_val, 0, 1023));
    ledcWrite(M1, constrain(m1_val, 0, 1023));
    ledcWrite(M2, constrain(m2_val, 0, 1023));
    ledcWrite(M3, constrain(m3_val, 0, 1023));
  }
}