#include <Ethernet.h>
#include <SPI.h>

//config ethernet
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

#define USE_DHCP
IPAddress ip(172, 16, 3, 22);


// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

bool isDhcp = true;




//relay controller
int r1 = LOW;
int r2 = LOW;
int r3 = LOW;
int r4 = LOW;
int rl1 = 4;
int rl2 = 5;
int rl3 = 6;
int rl4 = 7;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ethernet test!");
  ethernet_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  ethernet_loop();
}








/**
 * Ethernet logic functions
 */
void ethernet_setup() {
  Serial.println("start setup");
  // Open serial communications and wait for port to open:

  // start the Ethernet connection and the server:
#ifdef USE_DHCP
  if (Ethernet.maintain() % 2 == 1) {
      Serial.println("Cable disconnected or DHCP server hosed");
      
  } else {
    Serial.println("ethernet begin");
    if (Ethernet.begin(mac) == 0) {
      Serial.println("Failed to configure Ethernet using DHCP");
      // no point in carrying on, so do nothing forevermore:
      /*for (;;)
        ;
        */
    } else {
      Serial.println("ethernet begin ok");
    }
  }
#else
  Ethernet.begin(mac, ip);
  
#endif
  server.begin();
  Serial.print("server is at "+Ethernet.localIP());
  
}

void ethernet_loop() {
    // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        // Read the first line of the request
        String request = client.readStringUntil('\r');
        // Match the request
        if (request.indexOf("/R1=ON") != -1)  {
//          digitalWrite(rl1, HIGH);
          r1 = HIGH;          
        } 
        if (request.indexOf("/R1=OFF") != -1)  {
//          digitalWrite(rl1, LOW);
          r1 = LOW;          
        }
/*
        if (request.indexOf("/R2=ON") != -1)  {
          digitalWrite(rl2, HIGH);
          r2 = HIGH;
          
        } 
        if (request.indexOf("/R2=OFF") != -1)  {
          digitalWrite(rl2, LOW);
          r2 = LOW;
          
        }

        if (request.indexOf("/R3=ON") != -1)  {
          digitalWrite(rl3, HIGH);
          r3 = HIGH;
          
        } 
        if (request.indexOf("/R3=OFF") != -1)  {
          digitalWrite(rl3, LOW);
          r3 = LOW;
          
        }

        if (request.indexOf("/R4=ON") != -1)  {
          digitalWrite(rl4, HIGH);
          r4 = HIGH;
          
        } 
        if (request.indexOf("/R4=OFF") != -1)  {
          digitalWrite(rl4, LOW);
          r4 = LOW;
          
        }
          */
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 60");  // refresh the page automatically every 60 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 8; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
            Serial.print("analog input ");
            Serial.print(analogChannel);
            Serial.print(" is ");
            Serial.println(sensorReading);
            
          }
          client.println("<br /><h1>");
          client.print("Humidity: ");
//          client.print(humidity);
//          client.print(" %\t");
//          client.print("Temperature: ");
//          client.print(temperature);
//          client.print(" ");
//          client.print(DEGREE_UNIT);
//          client.print("\t");
//          client.print("Heat index: ");
//          client.println(heat_index);
//          client.print("</h1>");



//led control

          client.print("<h1>R1 - ");          
          if (r1 == HIGH) {
            client.print("On");
          } else {
            client.print("Off");
          }
          client.print("</h1>");
          client.println("<a href=\"/R1=ON\"\"><button>Turn On </button></a>");
          client.println("<a href=\"/R1=OFF\"\"><button>Turn Off </button></a><br />");
/*

          client.print("<h1>R2 - ");          
          if (r2 == HIGH) {
            client.print("On");
          } else {
            client.print("Off");
          }
          client.print("</h1>");
          client.println("<a href=\"/R2=ON\"\"><button>Turn On </button></a>");
          client.println("<a href=\"/R2=OFF\"\"><button>Turn Off </button></a><br />");


          client.print("<h1>R3 - ");          
          if (r3 == HIGH) {
            client.print("On");
          } else {
            client.print("Off");
          }
          client.print("</h1>");
          client.println("<a href=\"/R3=ON\"\"><button>Turn On </button></a>");
          client.println("<a href=\"/R3=OFF\"\"><button>Turn Off </button></a><br />");


          client.print("<h1>R4 - ");          
          if (r4 == HIGH) {
            client.print("On");
          } else {
            client.print("Off");
          }
          client.print("</h1>");
          client.println("<a href=\"/R4=ON\"\"><button>Turn On </button></a>");
          client.println("<a href=\"/R4=OFF\"\"><button>Turn Off </button></a><br />");
          */
//end led control



                  
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
/**
 * comment this becouse of memory low
  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");

      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");

      //print your local IP address:
      printIPAddress();
      break;

    default:
      //nothing happened
      break;

  }
*/
}
