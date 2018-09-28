#include <DHT.h>

class Dht11SensorRHL {
  public:
    void setup ( void );
    void loop ( void );
    void loopReadDht ( void );
    float dht[10][3] = { };
    unsigned long startMillis;
    unsigned long currentMillis;
    unsigned long period = 5000;
    bool serialPrint = true;
};


