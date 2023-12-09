/*--------------------------------------------------
  Helmut Schaefer based on Demo by Stefan Thesen
  Schalten zweier Lampen über 5V Relais

  code fuer WeMos D1 R2
  IP: 192.168.178.58

  2018.01.27

  In Betrieb genommen am 27.1.2018 10:00
  
  -----------------------------------------------*/

#include <ESP8266WiFi.h>

const char* ssid = "FRITZ!Powerline 1240E"; //SSID aus dem Router
const char* password = "10521912433534971110"; //Passwort für den Zugang zum WLAN

unsigned long ulReqcount = 0;
unsigned long ulReconncount = 0;

WiFiServer server(80);

void setup()
{
  pinMode(5, OUTPUT);  //Wemos Pin 3 für Relay 1
  digitalWrite(5, 0);
  pinMode(4, OUTPUT); //Wemos Pin 4 für Relay 2
  digitalWrite(5, 0);

  // start serial
  Serial.begin(9600); //Zur Ausgabe von Status Information auf dem seriellen Monitor
  delay(1);

  // inital connect
  WiFi.mode(WIFI_STA);
  WiFiStart();
}

void WiFiStart()
{
  ulReconncount++;

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop()
{
  // check if WLAN is connected
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFiStart();
  }

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  unsigned long ultimeout = millis() + 250;
  while (!client.available() && (millis() < ultimeout) )
  {
    delay(1);
  }
  if (millis() > ultimeout)
  {
    Serial.println("client connection time-out!");
    return;
  }

  // Read the first line of the request
  String sRequest = client.readStringUntil('\r');
  Serial.println(sRequest);
  client.flush();

  // stop client, if request is empty
  if (sRequest == "")
  {
    Serial.println("empty request! - stopping client");
    client.stop();
    return;
  }

  // get path; end of path is either space or ?
  String sPath = "", sParam = "", sCmd = "";
  String sGetstart = "GET ";
  int iStart, iEndSpace, iEndQuest;
  iStart = sRequest.indexOf(sGetstart);
  if (iStart >= 0)
  {
    iStart += +sGetstart.length();
    iEndSpace = sRequest.indexOf(" ", iStart);
    iEndQuest = sRequest.indexOf("?", iStart);

    // are there parameters?
    if (iEndSpace > 0)
    {
      if (iEndQuest > 0)
      {
        // there are parameters
        sPath  = sRequest.substring(iStart, iEndQuest);
        sParam = sRequest.substring(iEndQuest, iEndSpace);
        Serial.println(sPath);
        Serial.println(sParam);
      }
      else
      {
        // NO parameters
        sPath  = sRequest.substring(iStart, iEndSpace);
      }
    }
  }

  ///////////////////////////////////////////////////////////////////////////////
  // output parameters to serial, you may connect e.g. an Arduino and react on it
  ///////////////////////////////////////////////////////////////////////////////
  if (sParam.length() > 0)
  {
    int iEqu = sParam.indexOf("=");
    if (iEqu >= 0)
    {
      sCmd = sParam.substring(iEqu + 1, sParam.length());
      Serial.println(sCmd);
    }
  }

  ///////////////////////////
  // format the html response
  ///////////////////////////
  String sResponse, sHeader;

  ////////////////////////////
  // 404 for non-matching path
  ////////////////////////////
  if (sPath != "/")
  {
    sResponse = "<html><head><title>404 Not Found</title></head><body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";

    sHeader  = "HTTP/1.1 404 Not found\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }
  ///////////////////////
  // format the html page
  ///////////////////////
  else
  {
    ulReqcount++;
    sResponse  = "<html><head><title>Steuerung mit WeMos D1 </title></head><body>";
    sResponse += "<font color=\"#000000\"><body bgcolor=\"#11CC00\">";
    sResponse += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">";
    sResponse += "<h1> &nbsp Steuerung mit WeMos</h1>";
    sResponse += "  <BR>";
    sResponse += "<FONT SIZE=+1>";
    sResponse += "<p>Lampe 1 &nbsp  <a href=\"?pin=FUNCTION1ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=FUNCTION1OFF\"><button>ausschalten</button></a></p>";
    sResponse += "<p>Lampe 2 &nbsp  <a href=\"?pin=FUNCTION2ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=FUNCTION2OFF\"><button>ausschalten</button></a></p>";
    //    sResponse += "<p>Rote LED &nbsp &nbsp <a href=\"?pin=FUNCTION3ON\"><button>einschalten</button></a>&nbsp;<a href=\"?pin=FUNCTION3OFF\"><button>ausschalten</button></a></p>";

    //////////////////////
    // react on parameters
    //////////////////////
    if (sCmd.length() > 0)
    {
      if (sCmd.indexOf("FUNCTION1ON") >= 0)
      {
        digitalWrite(4, 0);
      }
      else if (sCmd.indexOf("FUNCTION1OFF") >= 0)
      {
        digitalWrite(4, 1);
      }

      if (sCmd.indexOf("FUNCTION2ON") >= 0)
      {
        digitalWrite(5, 0);
      }
      else if (sCmd.indexOf("FUNCTION2OFF") >= 0)
      {
        digitalWrite(5, 1);
      }
    }


    sResponse += "<FONT SIZE=-2>";
    sResponse += "<BR>Aufrufz&auml;hler=";
    sResponse += ulReqcount;
    sResponse += " - Verbindungsz&auml;hler=";
    sResponse += ulReconncount;
    sResponse += "<BR>";
    sResponse += "</body></html>";

    sHeader  = "HTTP/1.1 200 OK\r\n";
    sHeader += "Content-Length: ";
    sHeader += sResponse.length();
    sHeader += "\r\n";
    sHeader += "Content-Type: text/html\r\n";
    sHeader += "Connection: close\r\n";
    sHeader += "\r\n";
  }

  // Send the response to the client
  client.print(sHeader);
  client.print(sResponse);

  // and stop the client
  client.stop();
  Serial.println("Client disonnected");
}
