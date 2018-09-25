#include "FlashingLedRHL.h"
#include "Dht11SensorRHL.h"
#include "EthernetRHL.h"
#include "WaterLevelRHL.h"
#include "RelayControllerRHL.h"
#include "LcdRHL.h"

FlashingLedRHL fl;
Dht11SensorRHL dhts;
EthernetRHL eth;
WaterLevelRHL wl;
RelayControllerRHL rc;
LcdRHL lc;

void setup() {
  Serial.begin(9600);
  fl.setup();
  dhts.setup();
  eth.setup();
  wl.setup();
  //rc.setup();
  lc.setup();
}

void loop() {
  fl.loop();
  dhts.loop();
  eth.loop();
  wl.loop();
  //rc.loop();
  lc.loop();
  delay(1000);
}

