
#include <ESP8266WiFi.h>
WiFiServer server(80); //Initialize the server on Port 80

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("WeMosWifi", "12345678"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server
}

void loop() {
  // put your main code here, to run repeatedly:
  server.stop();
}
