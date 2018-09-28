//#include "FlashingLedRHL.h"
//#include "Dht11SensorRHL.h"
#include "EthernetRHL.h"
//#include "WaterLevelRHL.h"
//#include "RelayControllerRHL.h"
//#include "LcdRHL.h"


//FlashingLedRHL flashingLed;
//Dht11SensorRHL dhtSensors;
EthernetRHL ethernet;
//WaterLevelRHL waterLevel;
//RelayControllerRHL relayController;
//LcdRHL lcdOutput;

void setup() {
  Serial.begin(9600);
//  flashingLed.setup();
//  dhtSensors.serialPrint = false;
//  dhtSensors.setup();
  ethernet.setup();
//  waterLevel.serialPrint = false;
//  waterLevel.setup();
  //relayController.setup();
//  lcdOutput.setup();
}

void loop() {
//  flashingLed.loop();
//  dhtSensors.loop();
  ethernet.loop();
//  waterLevel.loop();
  //relayController.loop();
//  lcdOutput.loop();
}

//reset func
void(* resetFunc) (void) = 0; //declare reset function @ address 0
