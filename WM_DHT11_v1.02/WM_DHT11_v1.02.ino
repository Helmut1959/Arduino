//-------------------------------------------------------
//Helmut Schaefer
//2018.01.20
//Temperatur und Feuchtemessung und Anzeige in WebBrowser
//-------------------------------------------------------

#include <SimpleDHT.h>
#include <ESP8266WiFi.h>

const char* ssid = "FRITZ!Powerline 1240E"; //SSID aus dem Router
const char* password = "10521912433534971110"; //Passwort für den Zugang zum WLAN

unsigned long ulReqcount;
unsigned long ulReconncount;

const String htmlOK = "HTTP/1.1 200 OK";
const String htmlContentType = "ContentType: text/html";
const String htmlBegin = "<!DOCTYPE HTML><html>";
const String htmlLinks = "<head><link rel='stylesheet' href='http://progs.draeger-it.blog/wemosd1/d1.css'/><link rel='shortcut icon' href='http://progs.draeger-it.blog/wemosd1/favicon.ico' /></head><body>";
const String htmlEnd = "</body></html>";
const String htmlBreakLine = "</br>";

int T_Request = 1;
int pinDHT11 = 2;
SimpleDHT11 dht11;

WiFiServer server(80); //Port auf welchem der Server laufen soll.

void setup() {

  // setup globals

  ulReqcount = 0;
  ulReconncount = 0;

  Serial.begin(9600);
  delay(10); //10ms. Warten damit die Seriele Kommunikation aufgebaut wurde.

  // inital connect
  WiFi.mode(WIFI_STA);
  WiFiStart();

  /*
    Serial.print("Verbindungsaufbau zu ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); //Initialisieren der Wifi Verbindung.

    while (WiFi.status() != WL_CONNECTED) { //Warten bis die Verbindung aufgebaut wurde.
    delay(1000);
    //Einen Punkt auf der Seriellen Schnittstelle ausgeben so das der Benutzer erkennt dass, das Sketch noch läuft.
    Serial.print(".");
    }
    //Bei erfolgreicher Verbindung wird der folgende Text ausgeben.
    Serial.print("Mit ");
    Serial.print(ssid);
    Serial.println("erfolgreich verbunden!");
    server.begin(); // Starten des Servers.
    Serial.println("Server gestartet"); //Ausgabe auf der Seriellen Schnittstelle das der Server gestartet wurde.

    // Ausgabe der IP Adresse
    Serial.print("Adresse : http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");
  */

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

void printHtmlHeader( WiFiClient client) {
  client.println(htmlOK);
  client.println(htmlContentType);
  client.println("");
  client.println(htmlBegin);
  client.println(htmlLinks);
}

void loop() {

  // check if WLAN is connected
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFiStart();
  }


  //Prüfen ob sich ein Client verbunden hat, wenn nicht die Loop "verlassen"
  WiFiClient client = server.available();
  if (!client) {
    delay(10);
    return;
  }

  // Wenn sich ein Client verbunden hat solange warten bis Daten gesendet werden.
  Serial.println("Neuer Client verbunden.");

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


  //Lesen der Anfrage vom Client
  String sRequest = client.readStringUntil('\r');
  Serial.println(sRequest);
  client.flush();

 // stop client, if request is empty
  if(sRequest=="")
  {
    Serial.println("empty request! - stopping client");
    client.stop();
    return;
  }

  //Wenn in der Anfrage die Zeichenkette "/S1" vorkommt dann...
  if (sRequest.indexOf("/S1") != -1) {
    T_Request = 1;
  }
  //Gibt den Html Header auf der Antwort aus.
  printHtmlHeader(client);
  //Ab hier wird die Webseite zusammengesetzt.
  client.println("<div class='mainWrapper'>");

  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed");
    return;
  }

  client.println(htmlBreakLine);
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);
  client.print("<div class='headline'>Klicke <a href=\"/S1\">hier</a> um die Anzeigen zu aktualisieren");
  client.println("");
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);

  if (T_Request == 1) {
    client.print("Die <b>Temperatur </b> betraegt: ");
    client.print((int)temperature);
    client.println("  C");
    client.println(htmlBreakLine);
    client.println(htmlBreakLine);
    client.print("Die <b> Luftfeuchtigkeit </b> betraegt: ");
    client.print((int)humidity);
    client.println(" %");
    client.println(htmlBreakLine);
    client.println(htmlBreakLine);
    T_Request = 0;
  }
  client.println(htmlEnd);
  client.stop();
  Serial.println("Client disonnected");

  // DHT11 sampling rate is 1HZ.
  delay(100); //Minimaler Messabstand: 2 sec.
}
