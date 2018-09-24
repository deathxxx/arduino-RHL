#include <DHT.h>

DHT dht43(43, DHT11);
DHT dht44(44, DHT11);
DHT dht45(45, DHT11);
DHT dht46(46, DHT11);
DHT dht47(47, DHT11);
DHT dht48(48, DHT11);
DHT dht49(49, DHT11);
DHT dht50(50, DHT11);
DHT dht51(51, DHT11);
DHT dht52(52, DHT11);

void setup() {
  Serial.begin(9600);
  setupInitDht();
}

void loop() {

    loopReadDht();
    delay(1000);

}

void setupInitDht() {
  dht43.begin();
  dht44.begin();
  dht45.begin();
  dht46.begin();
  dht47.begin();
  dht48.begin();
  dht49.begin();
  dht50.begin();
  dht51.begin();
  dht52.begin();
}

void loopReadDht() {

    float dht [10][3];

    /*--------43----------*/
    dht[0][0] = 43;
    dht[0][1] = dht43.readHumidity();
    dht[0][2] = dht43.readTemperature();
    /*--------43----------*/
    /*--------44----------*/
    dht[1][0] = 44;
    dht[1][1] = dht44.readHumidity();
    dht[1][2] = dht44.readTemperature();
    /*--------44----------*/
    /*--------45----------*/
    dht[2][0] = 45;
    dht[2][1] = dht45.readHumidity();
    dht[2][2] = dht45.readTemperature();
    /*--------45----------*/
    /*--------46----------*/
    dht[3][0] = 46;
    dht[3][1] = dht46.readHumidity();
    dht[3][2] = dht46.readTemperature();
    /*--------46----------*/
    /*--------47----------*/
    dht[4][0] = 47;
    dht[4][1] = dht47.readHumidity();
    dht[4][2] = dht47.readTemperature();
    /*--------47----------*/
    /*--------48----------*/
    dht[5][0] = 48;
    dht[5][1] = dht48.readHumidity();
    dht[5][2] = dht48.readTemperature();
    /*--------48----------*/
    /*--------49----------*/
    dht[6][0] = 49;
    dht[6][1] = dht49.readHumidity();
    dht[6][2] = dht49.readTemperature();
    /*--------49----------*/
    /*--------50----------*/
    dht[7][0] = 50;
    dht[7][1] = dht50.readHumidity();
    dht[7][2] = dht50.readTemperature();
    /*--------50----------*/
    /*--------51----------*/
    dht[8][0] = 51;
    dht[8][1] = dht51.readHumidity();
    dht[8][2] = dht51.readTemperature();
    /*--------51----------*/
    /*--------52----------*/
    dht[9][0] = 52;
    dht[9][1] = dht52.readHumidity();
    dht[9][2] = dht52.readTemperature();
    /*--------52----------*/

    String out;
    for(int i=0; i<10; i++){
      out = out + "d"+(int)dht[i][0]+"/h:"+String(dht[i][1])+"/t/"+String(dht[i][2])+"|";
    }
    Serial.println(out);
//    Serial.println(dht[9][0]);
}

