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
  dht52.begin();
}

void loop() {

    float h52 = dht52.readHumidity();
    float t52 = dht52.readTemperature();

    if (isnan(h52) || isnan(t52)) {
      Serial.println("I can not read the testimony");
      return;
    }
    String out = "d52/h:"+String(h52)+"/t/"+String(t52);
    Serial.println(out);
    
    Serial.print("Humidity - ");
    Serial.print(h52);
    Serial.print("   ");
    Serial.print("Temperature - ");
    Serial.print(t52);
    Serial.print("\n");

    delay(1000);

}
