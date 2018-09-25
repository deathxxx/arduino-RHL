/* мигающий светодиод */
#include "FlashingLedRHL.h"
#include "Arduino.h"


void FlashingLedRHL::setup(){
  pinMode(led, OUTPUT);
}

void FlashingLedRHL::loop() {
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
}

