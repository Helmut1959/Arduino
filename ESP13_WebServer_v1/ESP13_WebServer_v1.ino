#include <SimpleDHT.h>

class BradMcCoy1969_WebServer{
  public:
  String inputString = ""; 
  String Message="";
  int pinDHT11 = 7;
  SimpleDHT11 dht11;
    
  BradMcCoy1969_WebServer(){
    inputString.reserve(200);
  }

  void handleClient(){
    while(Serial.available() > 0) {
      inputString += Serial.readString();
    }
    if (inputString.length() > 0){
      Message = readDHTSensor();
      handleRequest(inputString);
      inputString = "";
    }
  }

  void handleRequest(String someRequest){
    String Header="";
    String Page="";
    //GET /helpme HTTP/1.1 Host: 192.168.1.6:1969 Connection: keep-<r>71 *F, 20 %

    Page = Message;
    
    Header = getResponseStatusLine(200);
    Header += "Server: DoIt_WIFI\r\n";
    Header += "Content-Type: text/html\r\n";
    Header += "Connecdtion: close\r\n";
    Header += "Access-Control-Allow-Origin: *\r\n";
    Header += "Content-Length: ";
    Header.concat(Page.length());
    Header += "\r\n\r\n";

    writeResponse(Header + Page);
  }

  void writeResponse(String TheResponse){
    //this method will write out the response to the client
    //the write will be done in chunks
    //it just seems to need these small chunks with the time delay in order for it to work.
    int Max=30;
    int RemainingBytes=0;
    int TotalBytes=TheResponse.length();
    
    for (int i=0; i<TotalBytes; i+=Max){
      if (i+Max <= TotalBytes){
        Serial.print(TheResponse.substring(i,i+Max));
      }
      else {
        RemainingBytes=TotalBytes-i;
        Serial.print(TheResponse.substring(i,i+RemainingBytes));
      }
      Serial.flush();
      delay(400);
    }
  }

  String getResponseStatusLine(int ResponseCode){
    String StatusLine = "HTTP/1.0 ";
    StatusLine.concat(ResponseCode);
    StatusLine += " ";
    switch (ResponseCode){
      case 100:  StatusLine += " Continue"; break;
      case 101:  StatusLine += "Switching Protocols"; break;
      case 200:  StatusLine += "OK"; break;
      case 201:  StatusLine += "Created"; break;
      case 202:  StatusLine += "Accepted"; break;
      case 203:  StatusLine += "Non-Authoritative Information"; break;
      case 204:  StatusLine += "NO Content"; break;
      case 205:  StatusLine += "Reset Content"; break;
      case 206:  StatusLine += "Partial Content"; break;
      case 300:  StatusLine += "Multiple Choices"; break;
      case 301:  StatusLine += "Moved Permanently"; break;
      case 302:  StatusLine += "Found"; break;
      case 303:  StatusLine += "See Other"; break;
      case 304:  StatusLine += "Not Modified"; break;
      case 305:  StatusLine += "Use Proxy"; break;
      case 307:  StatusLine += "Temporary Redirect"; break;
      case 400:  StatusLine += "Bad Request"; break;
      case 401:  StatusLine += "Unauthorized"; break;
      case 402:  StatusLine += "Payment Required"; break;
      case 403:  StatusLine += "Forbidden"; break;
      case 404:  StatusLine += "Not Found"; break;
      case 405:  StatusLine += "Method Not Allowed"; break;
      case 406:  StatusLine += "Not Acceptable"; break;
      case 407:  StatusLine += "Proxy Authentication Required"; break;
      case 408:  StatusLine += "Request Time-out"; break;
      case 409:  StatusLine += "Conflict"; break;
      case 410:  StatusLine += "Gone"; break;
      case 411:  StatusLine += "Length Required"; break;
      case 412:  StatusLine += "Precondition Failed"; break;
      case 413:  StatusLine += "Request Entity Too Large"; break;
      case 414:  StatusLine += "Request-URL Too Large"; break;
      case 415:  StatusLine += "Unsupported Media Type"; break;
      case 416:  StatusLine += "Requested Range NOt Satifiable"; break;
      case 417:  StatusLine += "Expectation Failed"; break;
      case 500:  StatusLine += "Internal Server Error"; break;
      case 501:  StatusLine += "Not Implemented"; break;
      case 502:  StatusLine += "Bad Gateway"; break;
      case 503:  StatusLine += "Service Unavailable"; break;
      case 504:  StatusLine += "Gateway Time-out"; break;
      case 505:  StatusLine += "HTTP Version Not Supported"; break;
    }
    StatusLine += "\n\r";    
    return StatusLine;
  }

  String readDHTSensor(){
    // read with raw sample data.
    String Results="";
    byte temperature = 0;
    byte humidity = 0;
    byte data[40] = {0};
    if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
      return "Read DHT11 failed";
    }
    
    Results = (int)(temperature*9/5 + 32);
    Results += " F, ";
    Results.concat((int)humidity);
    Results += " %";  
    return Results;
  }  
};

//-----------------------------------------------------------------------

BradMcCoy1969_WebServer MyWebServer;

void setup() {
  Serial.begin(9600);
}

void loop() {
  MyWebServer.handleClient();
  delay(100);
}


