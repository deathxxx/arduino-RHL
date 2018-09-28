/* 
  Board: Duemilanove or Diecimila 
  Processor: ATmega328 
  Programmer: AVR-ISP mkII 
 
  UNO 5V BOARD 
  and Wiznet 5100 Ethernet Shield 
   
  X0 - RX - FTDI 
  X1 - TX - FTDI 
  2  DIG02 -  
  3  DIG03 -  
  4  DIG04 - SD CARD             / RESERVED 
  5  TIMR1 -  
  6  DIG06 - 
  7  DIG07 -  
  8  DIG08 -  
  9  DIG09 -  
  10 DIG10 - SPI ETHERNET SS     / RESERVED 
  11 DIG11 - SPI ETHERNET MOSI   / RESERVED 
  12 DIG12 - SPI ETHERNET MISO   / RESERVED 
  13 DIG13 - SPI ETHERNET SCK    / RESERVED (LED FLICKERS DURING SPI COMM) 
  22 ADC00 -  
  23 ADC01 -  
  24 ADC02 -  
  25 ADC03 -  
  26 ADC04 -  
  27 ADC05 -  
  18? ADC06 -  
  21? ADC07 -  
*/ 
 
#include <SPI.h> 
#include <Ethernet.h> 
#include "EthernetRHL.h" 
 
/* 
  MACRO for string handling from PROGMEM 
  https://todbot.com/blog/2008/06/19/how-to-do-big-strings-in-arduino/ 
  max 149 chars at once ... 
*/ 
char p_buffer[150]; 
#define P(str) (strcpy_P(p_buffer, PSTR(str)), p_buffer) 
 
// Ethernet Interface Settings 
byte mac[] =      { 0xAD, 0xDE, 0xEF, 0xBB, 0xFD, 0xDD }; 
IPAddress ip      (192, 168, 88, 22);  // Private static IP address 
IPAddress myDns   (192, 168, 88, 1);   // DNS is not needed for this example 
IPAddress gateway (0, 0, 0, 0);       // Default gateway disabled for security reasons 
IPAddress subnet  (255, 255, 255, 0); // Class C subnet; typical 
 
// HTTP lives on TCP port 80 
EthernetServer server(80); 
 
 






/* ******** NTP Server Settings ******** */
/* us.pool.ntp.org NTP server
   (Set to your time server of choice) */
IPAddress timeServer(192, 168, 88, 254);

/* Set this to the offset (in seconds) to your local time
   This example is GMT - 4 */
const long timeZoneOffset = -14400L; 
const int timeZone = +6;
//const int timeZone = 1;     // Central European Time
//const int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

/* Syncs to NTP server every 15 seconds for testing,
   set to 1 hour or more to be reasonable */
unsigned int ntpSyncTime = 3600;       


/* ALTER THESE VARIABLES AT YOUR OWN RISK */
// local port to listen for UDP packets
unsigned int localPort = 8888;
// NTP time stamp is in the first 48 bytes of the message
const int NTP_PACKET_SIZE= 48;     
// Buffer to hold incoming and outgoing packets
byte packetBuffer[NTP_PACKET_SIZE]; 
// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;                   
// Keeps track of how long ago we updated the NTP server
unsigned long ntpLastUpdate = 0;   
// Check last time clock displayed (Not in Production)
time_t prevDisplay = 0;      
/* ******** NTP Server Settings end***** */




 
 
 
void EthernetRHL::setup() 
{ 
  // start the Ethernet connection and the server: 
  Ethernet.begin(mac, ip); 
  server.begin();   

/* ******** NTP Server read start ***** */

    //Try to get the date and time
   int trys=0;
   while(!getTimeAndDate() && trys<10) {
     trys++;
   }

/* ******** NTP Server read end ***** */
} 
 
 
 
 
 
// string buffers for receiving URL and arguments 
char bufferUrl[256]; 
char bufferArgs[512]; 
int urlChars = 0; 
int argChars = 0; 
 
// number of characters read on the current line 
int lineChars = 0; 
 
// total # requests serviced 
long requests = 0; 
 
// connection state while receiving a request 
int state = 0; 
 
 
 
 
 
void EthernetRHL::loop() 
{ 
   // listen for incoming clients 
  EthernetClient client = server.available(); 
   
  if (client)  
  { 
    state = 0; 
    urlChars = 0; 
    argChars = 0; 
    lineChars = 0; 
    bufferUrl[0] = 0; 
    bufferArgs[0] = 0; 
 
    while (client.connected())  
    { 
      if (client.available())  
      { 
        // read and echo data received from the client 
        char c = client.read(); 
        Serial.print(c); 
 
        // ignore \r carriage returns, we only care about \n new lines 
        if (c == '\r') 
          continue;         
           
        // control what happens to the buffer: 
        if (state == 0 && c == '/') 
        { 
          // Begin receiving URL 
          state = 1;  
        } 
        else if (state == 1 && c == '?') 
        { 
          // Begin receiving args 
          state = 2; 
        } 
        else if ((state == 1 || state == 2) && c == ' ') 
        { 
          // Received full request URL and/or args 
          state = 3; 
        } 
        else if (state == 1 && urlChars < 255) 
        { 
            // Receiving URL (allow up to 255 chars + null terminator) 
            bufferUrl[urlChars++] = c; 
            bufferUrl[urlChars] = 0; 
        } 
        else if (state == 2 && argChars < 511) 
        { 
            // Receiving Args (allow up to 511 chars + null terminator) 
            bufferArgs[argChars++] = c; 
            bufferArgs[argChars] = 0; 
        } 
        else if (state == 3 && c == '\n' && lineChars == 0) 
        { 
          // Received a line with no characters; this means the client has ended their request 
          state = 4; 
        } 
 
        // record how many characters on the line so far: 
        if (c == '\n') 
          lineChars = 0; 
        else 
          lineChars++; 
 
        // OK to respond 
        if(state == 4) 
        { 
          // Response given 
          state = 5;  
 
          // increment internally for fun purposes 
          requests++; 
          Serial.print(P("Request # ")); 
          Serial.print(requests); 
          Serial.print(P(": ")); 
          Serial.println(bufferUrl); 
 
          // handle the response 
          respond(client); 
 
          // exit the loop 
          break; 
        } 
      } 
    } 
     
    // flush and close the connection: 
    client.flush(); 
    client.stop(); 
  } 

/* ******** NTP Server loop start ***** */
    // Update the time via NTP server as often as the time you set at the top
    if(now()-ntpLastUpdate > ntpSyncTime) {
      int trys=0;
      while(!getTimeAndDate() && trys<10){
        trys++;
      }
      if(trys<10){
        Serial.println("ntp server update success");
      }
      else{
        Serial.println("ntp server update failed");
      }
    }
  
    // Display the time if it has changed by more than a second.
    /**
     * comment for clean output
    if( now() != prevDisplay){
      prevDisplay = now();
      clockDisplay(); 
    }
    */
/* ******** NTP Server loop end ***** */
} 
 
 
 
 
/* 
  Typical request: GET /<request goes here>?firstArg=1&anotherArg=2 HTTP/1.1 
  State 0 - connection opened 
  State 1 - receiving URL 
  State 2 - receiving Arguments 
  State 3 - arguments and/or URL finished 
  State 4 - client has ended request, waiting for server to respond 
  State 5 - server has responded 
   
  Example of what the server receives: 
   
  GET /test.html HTTP/1.1 
  Host: 192.168.1.23 
  Connection: keep-alive 
  Cache-Control: max-age=0 
  Upgrade-Insecure-Requests: 1 
  User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 
  Accept-Encoding: gzip, deflate, sdch 
  Accept-Language: en-US,en;q=0.8 
*/ 
 
 
 
void EthernetRHL::respond(EthernetClient client) 
{ 
  if (strcmp(bufferUrl, P("")) == 0) 
  { 
    // Requested: /  (DEFAULT PAGE) 
     
    // send response header 
    sendHttpResponseOk(client); 
 
    // send html page 
    // max length:    -----------------------------------------------------------------------------------------------------------------------------------------------------  (149 chars) 
    client.println(P("<HTML><head><title>Welcome</title></head><body><h1>Welcome, visitor")); 
    client.print(requests); 
    client.println(P("!</h1>Click here to visit the <a href=/test.html>Test Page</a><p>")); 
    client.println(P("String output is stored in progmem to conserve RAM. That's what all the P( ) stuff is about. Buffer is big enough for 149 chars at once. ")); 
    client.println(P("Be careful not to exceed!<p><font color=red>This web server is not secured for public access. Use at your own risk.</font> ")); 
    client.println(P("If you want to use this in an actual product, at least leave the gateway IP setting disabled. You should consider a design where the Arduino acts")); 
    client.println(P("as the client, or maybe a design where the Arduino can only be contacted by a more fully-secured server.<p>Requests are echoed to the console")); 
    client.println(P("with baud rate of 115200. Have fun!<p><img src='https://cdn.meme.am/instances/250x250/54595677.jpg'/></body></html>")); 
  } 
  else if (strcmp(bufferUrl, P("test.html")) == 0) 
  { 
    // Requested: test.html 
     
    // send response header 
    sendHttpResponseOk(client); 
 
    // send html page 
    client.println(P("<HTML><head><title>Test Page</title></head><body><h1>Test Page</h1>")); 
    client.println(P("<br><b>Resource:</b> ")); 
    client.println(bufferUrl); 
    client.println(P("<br><b>Arguments:</b> ")); 
    client.println(bufferArgs); 
    // max length:    -----------------------------------------------------------------------------------------------------------------------------------------------------  (149 chars) 
    client.println(P("<br><br><form action='/test.html?' method='GET'>Test arguments: <input type=text name='arg1'/> <input type=submit value='GET'/></form>")); 
    client.println(P("</body></html>")); 
  } 
  else 
  { 
    // All other requests - 404 not found 
     
    // send 404 not found header (oops) 
    sendHttp404(client); 
    client.println(P("<HTML><head><title>Resource not found</title></head><body><h1>The requested resource was not found</h1>")); 
    client.println(P("<br><b>Resource:</b> ")); 
    client.println(bufferUrl); 
    client.println(P("<br><b>Arguments:</b> ")); 
    client.println(bufferArgs); 
    client.println(P("</body></html>")); 
  } 
} 
 
// 200 OK means the resource was located on the server and the browser (or service consumer) should expect a happy response 
void EthernetRHL::sendHttpResponseOk(EthernetClient client) 
{ 
  Serial.println(P("200 OK")); 
  Serial.println(); 
   
  // send a standard http response header 
  client.println(P("HTTP/1.1 200 OK")); 
  client.println(P("Content-Type: text/html")); 
  client.println(P("Connnection: close")); // do not reuse connection 
  client.println(); 
} 
 
// 404 means it ain't here. quit asking. 
void EthernetRHL::sendHttp404(EthernetClient client) 
{ 
  Serial.println(P("404 Not Found")); 
  Serial.println(); 
   
  client.println(P("HTTP/1.1 404 Not Found")); 
  client.println(P("Content-Type: text/html")); 
  client.println(P("Connnection: close")); // do not reuse connection 
  client.println(); 
} 







/* ******** NTP Server functions ***** */

// Do not alter this function, it is used by the system
int EthernetRHL::getTimeAndDate() {
   int flag=0;
   Udp.begin(localPort);
   EthernetRHL::sendNTPpacket(timeServer);
   delay(1000);
   if (Udp.parsePacket()){
     Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer
     unsigned long highWord, lowWord, epoch;
     highWord = word(packetBuffer[40], packetBuffer[41]);
     lowWord = word(packetBuffer[42], packetBuffer[43]); 
     epoch = highWord << 16 | lowWord;
     //epoch = epoch - 2208988800 + timeZoneOffset;
     epoch = epoch - 2208988800 + timeZone * SECS_PER_HOUR;
     flag=1;
     setTime(epoch);
     ntpLastUpdate = now();
   }
   return flag;
}

// Do not alter this function, it is used by the system
unsigned long EthernetRHL::sendNTPpacket(IPAddress& address)
{
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;
  packetBuffer[1] = 0;
  packetBuffer[2] = 6;
  packetBuffer[3] = 0xEC;
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;                 
  Udp.beginPacket(address, 123);
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket();
}

// Clock display of the time and date (Basic)
void EthernetRHL::clockDisplay(){
  Serial.print(hour());
  EthernetRHL::printDigits(minute());
  EthernetRHL::printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

// Utility function for clock display: prints preceding colon and leading 0
void EthernetRHL::printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


String EthernetRHL::clockDisplayText() {
  String out ="" 
  + EthernetRHL::getDigits(hour()) + ":"
  + EthernetRHL::getDigits(minute()) + ":"
  + EthernetRHL::getDigits(second()) + ":"
  + " " + day()
  + " " + month()
  + " " + year();
  return out;
}

String EthernetRHL::getDigits(int digits){
  String out = "";
  if(digits < 10)
    out = out + "0";
  out = out + digits;
  return out;
}
/* ******** NTP Server functions end ***** */
