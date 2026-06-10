#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int JOYSTICK_PIN = A0;   
const int ARM_BUTTON_PIN = 2;  
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

unsigned long lastSerialTime = 0;
const unsigned long SERIAL_TIMEOUT_MS = 100; // Drop data if PC lags

void setup() {
  Serial.begin(115200);
  
  pinMode(JOYSTICK_PIN, INPUT);
  pinMode(ARM_BUTTON_PIN, INPUT_PULLUP); 

  if (!radio.begin()) {
    while (1); 
  }
  
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW); 
  radio.stopListening();          
}

void loop() {
  // Check for fresh tracking data from the PC
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    int firstComma = input.indexOf(',');
    int secondComma = input.indexOf(',', firstComma + 1);
    
    if (firstComma != -1 && secondComma != -1) {
      radioData.droneX = input.substring(0, firstComma).toInt();
      radioData.droneY = input.substring(firstComma + 1, secondComma).toInt();
      radioData.droneZ = input.substring(secondComma + 1).toInt();
      lastSerialTime = millis(); // Reset PC watchdog
    }
  }

  // SAFETY WATCHDOG: If PC stops talking, invalidate coordinates
  if (millis() - lastSerialTime > SERIAL_TIMEOUT_MS) {
    radioData.droneX = -1;
    radioData.droneY = -1;
    radioData.droneZ = -1;
  }

  int rawThrottle = analogRead(JOYSTICK_PIN);
  radioData.throttle = map(rawThrottle, 0, 1023, 0, 255);
  
  radioData.armSwitch = (digitalRead(ARM_BUTTON_PIN) == LOW);

  bool success = radio.write(&radioData, sizeof(PacketData));
  
  if (success) {
    if (radioData.droneX == -1) {
      Serial.println("TX Mode: Manual Only (Vision Offline)");
    } else {
      Serial.print("TX Position -> X: "); Serial.print(radioData.droneX);
      Serial.print(" | Z: "); Serial.println(radioData.droneZ);
    }
  }

  delay(20); 
}