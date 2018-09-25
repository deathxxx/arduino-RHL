#include "WaterLevelRHL.h"
#include "Arduino.h"

//int A6pin = A6;
//int A7pin = A7;
//int A8pin = A8;
//int A9pin = A9;
//int A10pin = A10;

void WaterLevelRHL::setup() {
  startMillis = millis(); 
}

void WaterLevelRHL::loop() {
  currentMillis = millis();
  if(currentMillis - startMillis >= period) {
    int waterA6 = analogRead(A6); // read input value
    int waterA7 = analogRead(A7); // read input value
    int waterA8 = analogRead(A8); // read input value
    int waterA9 = analogRead(A9); // read input value
    int waterA10 = analogRead(A10); // read input value

    water[0][0] = 6;
    water[0][1] = waterA6;
    water[1][0] = 7;
    water[1][1] = waterA7;
    water[2][0] = 8;
    water[2][1] = waterA8;
    water[3][0] = 9;
    water[3][1] = waterA9;
    water[4][0] = 10;
    water[4][1] = waterA10;
  
    Serial.print("Water Level Value   ");
  
    Serial.print(" A6 - ");
    Serial.print(waterA6);
    Serial.print(" | ");
    Serial.print(" A7 - ");
    Serial.print(waterA7);
    Serial.print(" | ");
    Serial.print(" A8 - ");
    Serial.print(waterA8);
    Serial.print(" | ");
    Serial.print(" A9 - ");
    Serial.print(waterA9);
    Serial.print(" | ");
    Serial.print(" A10 - ");
    Serial.print(waterA10);
    Serial.print(" (");
    

    startMillis = currentMillis;
    Serial.print(currentMillis);  
    Serial.println(" millis)");
  }
}

