//Helmut Schaefer
//2018.01.19
//Achtung: Sketch funktioniert so nicht!!!!!




#include <SimpleDHT.h>
#include <ESP8266WiFi.h>

const char* ssid = "FRITZ!Powerline 1240E"; //SSID aus dem Router
const char* password = "10521912433534971110"; //Passwort für den Zugang zum WLAN

const String htmlOK = "HTTP/1.1 200 OK";
const String htmlContentType = "ContentType: text/html";
const String htmlBegin = "<!DOCTYPE HTML><html>";
const String htmlLinks = "<head><link rel='stylesheet' href='http://progs.draeger-it.blog/wemosd1/d1.css'/><link rel='shortcut icon' href='http://progs.draeger-it.blog/wemosd1/favicon.ico' /></head><body>";
const String htmlEnd = "</body></html>";
const String htmlBreakLine = "</br>";

int T_Request = 1;
WiFiServer server(80); //Port auf welchem der Server laufen soll.

int pinDHT11 = 2;
SimpleDHT11 dht11;

void setup() {
  Serial.begin(9600);
  delay(10); //10ms. Warten damit die Seriele Kommunikation aufgebaut wurde.
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
}

void printHtmlHeader( WiFiClient client) {
  client.println(htmlOK);
  client.println(htmlContentType);
  client.println("");
  client.println(htmlBegin);
  client.println(htmlLinks);
}


void loop() {
  WiFiClient client = server.available();

  printHtmlHeader(client);
  //Ab hier wird die Webseite zusammengesetzt.
  client.println("<div class='mainWrapper'>");

  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.println("Read DHT11 failed");
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

  client.print("Die Temperatur betraegt: ");
  client.print((int)temperature);
  client.println("  C");
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);
  client.print("Die Luftfeuchtigkeit betraegt: ");
  client.print((int)humidity);
  client.println(" %");
  client.println(htmlBreakLine);
  client.println(htmlBreakLine);

  // DHT11 sampling rate is 1HZ.
  delay(1000); //Minimaler Messabstand: 2 sec.
}
