volatile unsigned long lastBlinkTrigger = 0;
volatile bool startBlinking = false;
volatile int blinkCounter = 4;
volatile int ledState = HIGH;

void startBlink(int blinks) {
  startBlinking = true;
  lastBlinkTrigger = millis();
  blinkCounter = blinks * 2;
  ledState = LOW;
}

void handleBlinkLed() {
  unsigned long now = millis();
  if(startBlinking && (now - lastBlinkTrigger > (100))) {
    lastBlinkTrigger = millis();
    digitalWrite(led, ledState);
    ledState = !ledState;
    blinkCounter -= 1;
    if (blinkCounter == 0){
      startBlinking = false;
    }
  }
}