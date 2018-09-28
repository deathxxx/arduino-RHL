#include "FlashingLedRHL.h"
#include "EthernetRHL.h"
#include "Dht11SensorRHL.h"
#include "WaterLevelRHL.h"
#include "RelayControllerRHL.h"
#include "LcdRHL.h"


FlashingLedRHL flashingLed;
EthernetRHL ethernet;
Dht11SensorRHL dhtSensors;
WaterLevelRHL waterLevel;
RelayControllerRHL relayController;
LcdRHL lcdOutput;

unsigned long startMillisMain;
unsigned long currentMillisMain;
unsigned long periodMain = 5000;

void setup() {
  Serial.begin(9600);
  ethernet.setup();
  flashingLed.setup();
//  dhtSensors.serialPrint = false;
  dhtSensors.setup();
//  waterLevel.serialPrint = false;
  waterLevel.setup();
  //relayController.setup();
  lcdOutput.setup();
  startMillisMain = millis();
}

void loop() {
  
  ethernet.loop();
  flashingLed.loop();
  dhtSensors.loop();
  waterLevel.loop();
  //relayController.loop();
  lcdOutput.loop();

  currentMillisMain = millis();
  if(currentMillisMain - startMillisMain >= periodMain) {
    Serial.println (ethernet.clockDisplayText());
    startMillisMain = currentMillisMain;
  }
}

//reset func
void(* resetFunc) (void) = 0; //declare reset function @ address 0
