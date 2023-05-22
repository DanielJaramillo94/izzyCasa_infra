#include <Arduino.h>

volatile boolean state = false; // Declare state variable as volatile

void IRAM_ATTR timerISR() {
  state = !state;
  digitalWrite(LED_BUILTIN, state);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(312500); // 1 second = 312500 ticks (80 MHz / 256)

  // Attach the ISR (Interrupt Service Routine) to Timer1
  timer1_attachInterrupt(timerISR);
}

void loop() {
}
