/* мигающий светодиод */
#include "FlashingLedRHL.h"
#include "Arduino.h"


void FlashingLedRHL::setup(){
  pinMode(led, OUTPUT);
}

void FlashingLedRHL::loop() {
  if (FlashingLedRHL::on) {
    digitalWrite(led, LOW);
    FlashingLedRHL::on = false;
  } else {
    digitalWrite(led, HIGH);
    FlashingLedRHL::on = true;
  }
  
}

