#include <DHT.h>

class Dht11SensorRHL {
  public:
    void setup ( void );
    void loop ( void );
    void setupInitDht ( void );
    void loopReadDht ( void );
    float dht[10][3] = { };
};


