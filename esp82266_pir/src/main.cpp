#include <Arduino.h>

#define timeSeconds 10

// Set GPIOs for LED and PIR Motion Sensor
const int led = LED_BUILTIN;
const int motionSensor = 14;

// Timer: Auxiliary variables
unsigned long now;
unsigned long lastTrigger = 0;
boolean startTimer = false;

void IRAM_ATTR detectsMovement();

void setup() {
  Serial.begin(115200);
  pinMode(motionSensor, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(motionSensor), detectsMovement, RISING);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Motion stopped...");
    digitalWrite(led, HIGH);
    startTimer = false;
  }
}

void IRAM_ATTR detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  digitalWrite(led, LOW);
  startTimer = true;
  lastTrigger = millis();
}
