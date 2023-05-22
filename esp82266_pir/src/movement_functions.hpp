#define timeSeconds 10

// Timer: Auxiliary variables
unsigned long now;
unsigned long lastTrigger = 0;
bool startTimer = false;

void IRAM_ATTR detectsMovement() {
  Serial.println("MOTION DETECTED!!!");
  digitalWrite(led, LOW);
  startTimer = true;
  lastTrigger = millis();
}

void IRAM_ATTR checkIfTurnOffLed() {
  now = millis();
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Motion stopped...");
    digitalWrite(led, HIGH);
    startTimer = false;
  }
}