#include <DHT.h>
#define DHTPIN 52

DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("I can not read the testimony");
      return;
    }
    Serial.print("Humidity - ");
    Serial.print(h);
    Serial.print("   ");
    Serial.print("Temperature - ");
    Serial.print(t);
    Serial.print("\n");

    delay(1000);

}
