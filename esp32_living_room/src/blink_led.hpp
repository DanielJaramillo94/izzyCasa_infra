volatile unsigned long lastBlinkTrigger = 0;
volatile bool startBlinking = false;
volatile int blinkCounter = 4;
volatile int ledState = HIGH;

void startBlink(int blinks) {
  startBlinking = true;
  lastBlinkTrigger = millis();
  blinkCounter = blinks * 2;
  digitalWrite(led, HIGH);
}

void handleBlinkLed() {
  unsigned long now = millis();
  if(startBlinking && (now - lastBlinkTrigger > (3000))) {
    digitalWrite(led, LOW);
    startBlinking = false;    
  }
}