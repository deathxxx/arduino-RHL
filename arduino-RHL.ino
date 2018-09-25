#include "FlashingLedRHL.h"
#include "Dht11SensorRHL.h"
#include "EthernetRHL.h"

FlashingLedRHL fl;
Dht11SensorRHL dhts;
EthernetRHL eth;

void setup() {
  Serial.begin(9600);
  fl.setup();
  dhts.setup();
  eth.setup();
}

void loop() {
  fl.loop();
  dhts.loop();
  eth.loop();
  delay(1000);
}

