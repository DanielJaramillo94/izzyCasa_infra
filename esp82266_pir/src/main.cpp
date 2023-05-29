
#include <Arduino.h>

const int SECONDS_IN_MILLIS = 1000;
const int led = LED_BUILTIN;
const int motionSensor = 14;
#include "blink_led.hpp"

#include "wifi.hpp"
#include "mqtt.hpp"
#include "dht11.hpp"

#include "movement_functions.hpp"

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  ConnectWiFi_STA();
  DTHsetup();
  InitMqtt();
}

void loop() {
  unsigned long now = millis();
  handleBlinkLed(now);
  handleMqtt();
  DTHloop(now);
}
