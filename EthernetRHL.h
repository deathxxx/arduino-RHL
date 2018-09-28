#include <Ethernet.h>
#include <TimeLib.h>
class EthernetRHL {
  public:
    void setup ( void );
    void loop ( void );
    void respond ( EthernetClient client );
    void sendHttpResponseOk ( EthernetClient client );
    void sendHttp404 ( EthernetClient client );

    int getTimeAndDate( void );
    unsigned long sendNTPpacket(IPAddress& address);
    void clockDisplay( void );
    void printDigits( int digits );

    String EthernetRHL::clockDisplayText();
    String EthernetRHL::getDigits(int digits);
};

