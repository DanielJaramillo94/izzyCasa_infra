#include <Arduino.h>

const int LED_ROOM_0 = 5;
const int LED_ROOM_1 = 18;
const int LED_ROOM_2 = 19;
#include "blink_led.hpp"

#include "wifi.hpp"
#include "mqtt.hpp"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_ROOM_0, OUTPUT);
  digitalWrite(LED_ROOM_0, LOW);

  pinMode(LED_ROOM_1, OUTPUT);
  digitalWrite(LED_ROOM_1, LOW);

  pinMode(LED_ROOM_2, OUTPUT);
  digitalWrite(LED_ROOM_2, LOW);

  ConnectWiFi_STA();
  InitMqtt();
}

void loop() {
  handleBlinkLed();
  handleMqtt();
}