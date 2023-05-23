
// Timer: Auxiliary variables
unsigned long now;
volatile unsigned long lastTrigger = 0;
volatile bool startTimer = false;
volatile int blinkCounter = 4;
volatile int ledState = HIGH;

void IRAM_ATTR detectsMovement() {
  publishMessage(MQTT_TOPIC_NAME, "1");
  startTimer = true;
  lastTrigger = millis();
  blinkCounter = 4;
  ledState = LOW;
}

void blinkLed() {
  now = millis();
  if(startTimer && (now - lastTrigger > (100))) {
    lastTrigger = millis();
    digitalWrite(led, ledState);
    ledState = !ledState;
    blinkCounter -= 1;
    if (blinkCounter == 0){
      startTimer = false;
    }
  }
}