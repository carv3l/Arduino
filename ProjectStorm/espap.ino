/*
Geekstips.com
IoT project - Communication between two ESP8266 - Talk with Each Other
ESP8266 Arduino code example
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// IoT platform Credentials
String apiKey = "20HRVWVYRKW1ZJ3M";
const char* logServer = "api.thingspeak.com";

String slave_chuva = "192.168.4.4";

// Internet router credentials
const char* ssid = "espAP";
const char* password = "poiou123";

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;

ESP8266WebServer server(80);
WiFiClient client;


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_AP_STA);
  setupAccessPoint();
 startMillis = millis();  //initial start time
  
}

// Handling the / root web page from my server
void handle_index() {
  server.send(200, "text/plain", "Get the f**k out from my server!");
}

// Handling the /feed page from my server
void handle_feed() {
   if (currentMillis - startMillis >= 1500)  //test whether the period has elapsed
  {
  String data = server.arg("field1");
  String ipaddress = server.arg("field2");
  Serial.println(data);
  Serial.println(ipaddress);
  if(ipaddress == slave_chuva){
  setupStMode(data);
  }
  startMillis = currentMillis;
  }

  
}

void setupAccessPoint(){
  Serial.println("** SETUP ACCESS POINT **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("- start ap with SID: "+ String(ssid));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("- AP IP address is :");
  Serial.print(myIP);
  setupServer();
}

void setupServer(){  
  Serial.println("** SETUP SERVER **");
  Serial.println("- starting server :");
  server.on("/", handle_index);
  server.on("/feed", handle_feed);
  server.begin();
};

void setupStMode(String field1){
  Serial.println("** SETUP STATION MODE **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println();
  Serial.println("- connecting to Home Router SID: **********");
  WiFi.begin("IPG-Free");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  Serial.println("- connecting to Database server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(field1);
    postStr += "\r\n\r\n";
    Serial.println("- sending data...");
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
  /** If your ESP does not respond you can just
  *** reset after each request sending 
  Serial.println("- trying reset");
  ESP.reset();
  **/
}

void loop() {
 int statusc = client_status();
//server.send(200, "text/html", "<form action=\"/LED\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>");
sendHttpRequest();

if(statusc >= 1){
        
        delay(1000);
       server.handleClient();
       
    }

    currentMillis = millis();
  
  
}

int client_status() {
 
  unsigned char number_client;
  
  number_client= wifi_softap_get_station_num();

  Serial.print(" Total Connected Clients are = ");
  Serial.println(number_client);
  

  
  delay(500);
  return number_client;
}


void sendHttpRequest() {
  HTTPClient http;
  http.begin("192.168.4.4");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST("response=OLA");
  http.writeToStream(&Serial);
  http.end();
}
