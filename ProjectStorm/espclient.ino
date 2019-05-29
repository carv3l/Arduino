#include <SoftwareSerial.h>
#define RX 10
#define TX 11


String AP = "espAP";       // CHANGE ME
String PASS = "poiou123"; // CHANGE ME
//String API = "20HRVWVYRKW1ZJ3M";   // CHANGE ME
String HOST = "192.168.4.1";
String URI = "/feed";
String PORT = "80";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;

const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum


SoftwareSerial esp8266(RX,TX); 
//ESP8266WebServer server(80);


  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");


  
  sendCommand("AT+CIPSTA=\"192.168.4.4\",\"192.168.4.1\",\"255.255.255.0\"",20,"OK");
}
void loop() {

  int sensorReading = analogRead(A0);
  float percent = map(sensorReading, 1024, 0, 0, 100);

  Serial.println((String)"Percentagem:"+percent);
  Serial.println(esp8266.find("temp"));
 if (percent > 29){
  String getData = "field1="+String(percent);
  getData += "&field2=192.168.4.4";
  httppost(getData);
  }
 

}

void httppost (String getData) {
esp8266.println("AT+CIPSTART=\"TCP\",\"" + HOST + "\",80");//start a TCP connection.
if( esp8266.find("OK")) {
Serial.println("TCP connection ready");
} delay(1000);
String postRequest = "POST " + URI + " HTTP/1.0\r\n" + 
"Host: " + HOST + "\r\n" +
"Accept: *" + "/" + "*\r\n" +
"Content-Length: " + getData.length() + "\r\n" +
"Content-Type: application/x-www-form-urlencoded\r\n" +
"\r\n" + getData;
String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.
esp8266.print(sendCmd);
esp8266.println(postRequest.length() );
delay(500);
if(esp8266.find(">")) { Serial.println("Sending.."); esp8266.print(postRequest);
if( esp8266.find("SEND OK")) { Serial.println("Packet sent");
while (esp8266.available()) {
String tmpResp = esp8266.readString();
Serial.println(tmpResp);
}
// close the connection
esp8266.println("AT+CIPCLOSE");
}
}
}



void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(" Command: ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
    Serial.print(".");
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println(" RESPONSE : OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
