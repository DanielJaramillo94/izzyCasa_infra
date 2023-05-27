
#include <Arduino.h>
#include "Keypad.h"
#include <Servo.h>

Servo servo;
const int led = LED_BUILTIN;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

#include "blink_led.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"

#define servoPin 5

byte rowPins[ROWS] = {13, 12, 14, 27}; 
byte colPins[COLS] = {26, 25, 33};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
String code = "";

void getCode(){
  char key = keypad.getKey();

  if (key){
    code = code + key;
    if(code.length() == 6){
      Serial.println("6");
      publishMessage("keypads/mainDoor", code.c_str());
      code = "";
    }
    
  }
}

void setup() {
  Serial.begin(115200);
  //attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);
  pinMode(led, OUTPUT);
  servo.attach(servoPin);
  servo.write(0);
  digitalWrite(led, LOW);
  ConnectWiFi_STA();
  InitMqtt();
}

void loop() {
  handleBlinkLed();
  handleMqtt();
  getCode();
}
