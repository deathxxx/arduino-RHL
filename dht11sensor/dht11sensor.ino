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
    /*--------43----------*/
    float h43 = dht43.readHumidity();
    float t43 = dht43.readTemperature();

    if (isnan(h43) || isnan(t43)) {
      Serial.println("I can not read the testimony 43");
//      return;
    }
    String out43 = "d43/h:"+String(h43)+"/t/"+String(t43)+"|";
    /*--------43----------*/
    /*--------44----------*/
    float h44 = dht44.readHumidity();
    float t44 = dht44.readTemperature();

    if (isnan(h44) || isnan(t44)) {
      Serial.println("I can not read the testimony 44");
//      return;
    }
    String out44 = "d44/h:"+String(h44)+"/t/"+String(t44)+"|";
    /*--------44----------*/
    /*--------45----------*/
    float h45 = dht45.readHumidity();
    float t45 = dht45.readTemperature();

    if (isnan(h45) || isnan(t45)) {
      Serial.println("I can not read the testimony 45");
//      return;
    }
    String out45 = "d45/h:"+String(h45)+"/t/"+String(t45)+"|";
    /*--------45----------*/
    /*--------46----------*/
    float h46 = dht46.readHumidity();
    float t46 = dht46.readTemperature();

    if (isnan(h46) || isnan(t46)) {
      Serial.println("I can not read the testimony 46");
//      return;
    }
    String out46 = "d46/h:"+String(h46)+"/t/"+String(t46)+"|";
    /*--------46----------*/
    /*--------47----------*/
    float h47 = dht47.readHumidity();
    float t47 = dht47.readTemperature();

    if (isnan(h47) || isnan(t47)) {
      Serial.println("I can not read the testimony 47");
//      return;
    }
    String out47 = "d47/h:"+String(h47)+"/t/"+String(t47)+"|";
    /*--------47----------*/
    /*--------48----------*/
    float h48 = dht48.readHumidity();
    float t48 = dht48.readTemperature();

    if (isnan(h48) || isnan(t48)) {
      Serial.println("I can not read the testimony 48");
//      return;
    }
    String out48 = "d48/h:"+String(h48)+"/t/"+String(t48)+"|";
    /*--------48----------*/
    /*--------49----------*/
    float h49 = dht49.readHumidity();
    float t49 = dht49.readTemperature();

    if (isnan(h49) || isnan(t49)) {
      Serial.println("I can not read the testimony 49");
//      return;
    }
    String out49 = "d49/h:"+String(h49)+"/t/"+String(t49)+"|";
    /*--------49----------*/
    /*--------50----------*/
    float h50 = dht50.readHumidity();
    float t50 = dht50.readTemperature();

    if (isnan(h50) || isnan(t50)) {
      Serial.println("I can not read the testimony 50");
//      return;
    }
    String out50 = "d50/h:"+String(h50)+"/t/"+String(t50)+"|";
    /*--------50----------*/
    /*--------51----------*/
    float h51 = dht51.readHumidity();
    float t51 = dht51.readTemperature();

    if (isnan(h51) || isnan(t51)) {
      Serial.println("I can not read the testimony 51");
//      return;
    }
    String out51 = "d51/h:"+String(h51)+"/t/"+String(t51)+"|";
    /*--------51----------*/
    /*--------52----------*/
    float h52 = dht52.readHumidity();
    float t52 = dht52.readTemperature();

    if (isnan(h52) || isnan(t52)) {
      Serial.println("I can not read the testimony 52");
      return;
    }
    String out52 = "d52/h:"+String(h52)+"/t/"+String(t52)+"|";
    /*--------52----------*/

    String out = out43+out44+out45+out46+out47+out47+out49+out50+out51+out52;
//    for(int i=46; i<=52; i++){
//      out = out + 
//    }
    Serial.println(out);
    
}

