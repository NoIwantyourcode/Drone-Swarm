#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int MOTOR_PIN = 4;      
const int CE_PIN = 9;         
const int CSN_PIN = 10;       

RF24 radio(CE_PIN, CSN_PIN);
const byte address[6] = "00001"; 

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

void setup() {
  Serial.begin(115200);
  
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0); 

  if (!radio.begin()) {
    while (1); 
  }
  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW); 
  radio.startListening();        
}

void loop() {
  if (radio.available()) {
    radio.read(&radioData, sizeof(PacketData));
    lastSignalTime = millis(); 

    if (radioData.armSwitch && radioData.throttle < 10 && radioData.droneX != -1) {
      isArmed = true; 
    } else if (!radioData.armSwitch || radioData.droneX == -1) {
      isArmed = false; 
    }

    if (isArmed) {
      analogWrite(MOTOR_PIN, radioData.throttle);
      Serial.print("Flight Normal | Z-Height: ");
      Serial.println(radioData.droneZ);
    } else {
      analogWrite(MOTOR_PIN, 0);
      if (radioData.droneX == -1) {
        Serial.println("SAFETY LOCKED: Tracking Lost or PC Offline!");
      } else {
        Serial.println("Locked: Unarmed");
      }
    }
  }

  if (millis() - lastSignalTime > TIMEOUT_MS) {
    isArmed = false;
    analogWrite(MOTOR_PIN, 0);
    Serial.println("TIMEOUT: Radio Link Dropped!");
  }
}