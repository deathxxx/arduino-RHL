class EthernetRHL {
  public:
    void setup ( void );
    void loop ( void );
    void respond ( EthernetClient client );
    void sendHttpResponseOk ( EthernetClient client );
    void sendHttp404 ( EthernetClient client );
};

