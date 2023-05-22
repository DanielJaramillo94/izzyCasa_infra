#include <Arduino.h>


const int ledPin =  LED_BUILTIN;
const long interval = 1000;

volatile boolean state = false; // Declare state variable as volatile

int ledState = LOW; 
unsigned long previousMillis = 0;  

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    ledState = (ledState == LOW) ? HIGH : LOW;

    digitalWrite(ledPin, ledState);
  }
}
