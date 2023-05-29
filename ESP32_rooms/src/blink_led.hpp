volatile unsigned long lastBlinkTrigger = 0;
volatile bool startBlinking = false;
volatile int blinkCounter;
volatile int ledState;

void startBlink(int blinks) {
  startBlinking = true;
  lastBlinkTrigger = millis();
  blinkCounter = blinks * 2 - 1;
  digitalWrite(LED_BUILTIN, HIGH);
  ledState = LOW;
}

void handleBlinkLed() {
  unsigned long now = millis();
  if(startBlinking && (now - lastBlinkTrigger > (100))) {
    lastBlinkTrigger = millis();
    digitalWrite(LED_BUILTIN, ledState);
    ledState = !ledState;
    blinkCounter -= 1;
    if (blinkCounter == 0){
      startBlinking = false;
    }
  }
}