
#include <Arduino.h>

const int led = LED_BUILTIN;
#include "blink_led.hpp"

#include "wifi.hpp"
#include "mqtt.hpp"


void setup() {
  Serial.begin(115200);
  //attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  ConnectWiFi_STA();
  InitMqtt();
}

void loop() {
  handleBlinkLed();
  handleMqtt();
}
