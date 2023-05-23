#include <Arduino.h>
#include "wifi.hpp"

const int led = LED_BUILTIN;
const int motionSensor = 14;

#include "movement_functions.hpp"

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  ConnectWiFi_STA();
}

void loop() {
  checkIfTurnOffLed();
}
