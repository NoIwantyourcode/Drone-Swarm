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
};
PacketData radioData;

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
  int rawThrottle = analogRead(JOYSTICK_PIN);
  radioData.throttle = map(rawThrottle, 0, 1023, 0, 255);
  
  radioData.armSwitch = (digitalRead(ARM_BUTTON_PIN) == LOW);

  bool success = radio.write(&radioData, sizeof(PacketData));
  
  if (success) {
    Serial.print("Throttle: ");
    Serial.print(radioData.throttle);
    Serial.print(" | Armed: ");
    Serial.println(radioData.armSwitch ? "YES" : "NO");
  } else {
    Serial.println("Error");
  }

  delay(20); 
}