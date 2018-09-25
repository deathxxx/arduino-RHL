#include "FlashingLedRHL.h"
#include "Dht11SensorRHL.h"

FlashingLedRHL fl;
Dht11SensorRHL dhts;

void setup() {
  Serial.begin(9600);
  dhts.setup();
  fl.setup();
}

void loop() {
  fl.loop();
  dhts.loop();
}

