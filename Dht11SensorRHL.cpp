#include "Arduino.h"
#include <DHT.h>
#include "Dht11SensorRHL.h"

DHT dht40(40, DHT11);
DHT dht41(41, DHT11);
DHT dht42(42, DHT11);
DHT dht43(43, DHT11);
DHT dht44(44, DHT11);
DHT dht45(45, DHT11);
DHT dht46(46, DHT11);
DHT dht47(47, DHT11);
DHT dht48(48, DHT11);
DHT dht49(49, DHT11);

void Dht11SensorRHL::setup() {
  dht40.begin();
  dht41.begin();
  dht42.begin();
  dht43.begin();
  dht44.begin();
  dht45.begin();
  dht46.begin();
  dht47.begin();
  dht48.begin();
  dht49.begin();  

  startMillis = millis(); 
}

void Dht11SensorRHL::loop() {
  currentMillis = millis();
  if(currentMillis - startMillis >= period) {
  
    /*--------40----------*/
    dht[0][0] = 40;
    dht[0][1] = dht40.readHumidity();
    dht[0][2] = dht40.readTemperature();
    /*--------40----------*/
    /*--------41----------*/
    dht[1][0] = 41;
    dht[1][1] = dht41.readHumidity();
    dht[1][2] = dht41.readTemperature();
    /*--------41----------*/
    /*--------42----------*/
    dht[2][0] = 42;
    dht[2][1] = dht42.readHumidity();
    dht[2][2] = dht42.readTemperature();
    /*--------42----------*/
    /*--------43----------*/
    dht[3][0] = 43;
    dht[3][1] = dht43.readHumidity();
    dht[3][2] = dht43.readTemperature();
    /*--------43----------*/
    /*--------44----------*/
    dht[4][0] = 44;
    dht[4][1] = dht44.readHumidity();
    dht[4][2] = dht44.readTemperature();
    /*--------44----------*/
    /*--------45----------*/
    dht[5][0] = 45;
    dht[5][1] = dht45.readHumidity();
    dht[5][2] = dht45.readTemperature();
    /*--------45----------*/
    /*--------46----------*/
    dht[6][0] = 46;
    dht[6][1] = dht46.readHumidity();
    dht[6][2] = dht46.readTemperature();
    /*--------46----------*/
    /*--------47----------*/
    dht[7][0] = 47;
    dht[7][1] = dht47.readHumidity();
    dht[7][2] = dht47.readTemperature();
    /*--------47----------*/
    /*--------48----------*/
    dht[8][0] = 48;
    dht[8][1] = dht48.readHumidity();
    dht[8][2] = dht48.readTemperature();
    /*--------48----------*/
    /*--------49----------*/
    dht[9][0] = 49;
    dht[9][1] = dht49.readHumidity();
    dht[9][2] = dht49.readTemperature();
    /*--------49----------*/

    startMillis = currentMillis;

    Dht11SensorRHL::sensorText = "";
    for(int i=0; i<10; i++){
      Dht11SensorRHL::sensorText = Dht11SensorRHL::sensorText + "d"+(int)dht[i][0]+"/h:"+String(dht[i][1])+"/t/"+String(dht[i][2])+"|";
    }
    Dht11SensorRHL::sensorText = Dht11SensorRHL::sensorText + "(" + currentMillis + " millis) ";
    if (serialPrint) {
    
      Serial.println(Dht11SensorRHL::sensorText);
    }

    
  }
}

