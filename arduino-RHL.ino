#include "FlashingLedRHL.h"
#include "Dht11SensorRHL.h"
#include "EthernetRHL.h"
#include "WaterLevelRHL.h"
#include "RelayControllerRHL.h"

FlashingLedRHL fl;
Dht11SensorRHL dhts;
EthernetRHL eth;
WaterLevelRHL wl;
RelayControllerRHL rc;

void setup() {
  Serial.begin(9600);
  fl.setup();
  dhts.setup();
  eth.setup();
  wl.setup();
  rc.setup();
}

void loop() {
  fl.loop();
  dhts.loop();
  eth.loop();
  wl.loop();
  rc.loop();
  delay(1000);
}

