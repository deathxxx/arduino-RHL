class WaterLevelRHL {
  public: 
    void setup ( void );
    void loop ( void );
    int water[5][2] = { };
    unsigned long startMillis;
    unsigned long currentMillis;
    unsigned long period = 5000;
};

