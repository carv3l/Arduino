#include <ESP8266WiFi.h>
 
String apiKey = "TVBFW2L618IPG3TV";
const char* ssid = "IPG-Free";
//const char* password = "w50w9exngc6KE";
const char* server = "api.thingspeak.com";

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

//#define rainsensor D7
 
WiFiClient client;
 
void setup() 
{
Serial.begin(115200);
delay(10);

  //pinMode(rainsensor, INPUT);
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid);
 
while (WiFi.status() != WL_CONNECTED) 
{
delay(500);
Serial.print(".");
}
Serial.println("WiFi connected");
 
}

 
void loop() 
{
 int sensorReading = analogRead(A0);

 float percent = map(sensorReading, 1024, 0, 0, 100);

 

 
if (client.connect(server,80)) {
String postStr = apiKey;
postStr +="&field3=";
postStr += String(percent);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

Serial.println("Sending data to Thingspeak");
}
client.stop();



Serial.println(percent);

delay(2000);

}
