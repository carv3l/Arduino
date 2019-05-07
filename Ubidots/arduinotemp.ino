#include "UbidotsESPMQTT.h"
#include <WEMOS_SHT3X.h>

//#include <WifiUDP.h>
//#include <NTPClient.h>
#include <Time.h>


//Variavel para a hora
int time_hour = 0;



//abrir ligação ao sensor de humidade e temperatura
SHT3X sht30(0x45); 

//variáveis
unsigned long inicio;
unsigned long fim;

int relayPin = D0;
int ledPin = D5;

float sensor_valueT;
float sensor_valueH;
/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "A1E-wVvY89d4ycWOIwcHQo7h8ElopQpbAt" // Your Ubidots TOKEN
#define WIFINAME "IPG-Free"//"WiFi-Informatica" //"IPG-Free" //Your SSID
#define WIFIPASS NULL // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
  Serial.print((char)payload[i]);
  }
  
  
  Serial.println();
}
/****************************************
 * Main Functions
 ****************************************/
void setup() {
  //client.ubidotsSetBroker("business.api.ubidots.com"); // Sets the broker properly for the business account
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(false); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  inicio=millis();
  /*
  Configura o relogio do servidor ntp portugues "pt.pool.ntp.org" , a primeira variavel pedida que é zero é em relacao ao avanco das horas,
  por exemplo se forem 21 e na variavel esteja escrito 1*3600 , significa que avança uma hora
  a segunda variavel é a mesma coisa só que para os minutos, se estiver por exemplo 7200, avanca 120 minutos
  */
  configTime(0,0,"pt.pool.ntp.org");
  Serial.println("\nWaiting for time");
  //para verificar que extraimos o relogio do server
  while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
  }

  
  }

void loop() {
  /*Este bloco vai buscar as horas,converte para um formato 
  em que seja possivel extrair o que necessitamos

  exemplos:
   tm_sec        Segundos     
   tm_min        Minutos                             
   tm_hour       Horas                       
   tm_mday       Dia              
   tm_mon        Mês                 
   tm_year       Ano
  */
  time_t now = time(nullptr);
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);  
  time_hour = timeinfo->tm_hour;

  //Imprimir a data e hora atual
  Serial.println(ctime(&now));
/*
 O seguinte ciclo se é executado se as horas que extraimos no bloco acima forem entre as 7 e as 9 da manha, e à noite entre as 21 e as 23
 a logica deste ciclo é para evitar que o aquecedor sobreaqueca devido há variação de temperatura que possa ocurrer durante o dia,
 ja que ele pode estar constatemente a ser ligado e desligado, assim quando forem 7 da manha por exemplo , ele começa a aquecer,
 tomo banho as 8 já com a casa de banho preparada
 evita tambem receber notificacões desnecessárias ao longo do dia

Está contido dentro do ciclo o restante codigo
*/
  

  if(time_hour>= 7 && time_hour <= 9 || time_hour >= 21 && time_hour <= 23 ){
    sensor_valueT = analogRead(A0);
  sensor_valueH = analogRead(A0);

  if(sht30.get()==0){    
      sensor_valueT=sht30.cTemp;
      sensor_valueH=sht30.humidity;     
  }

  // put your main code here, to run repeatedly:
  if(!client.connected()){
    Serial.println("nova tentativa de ligação");
      client.reconnect();

      
  
       
      }
  
  // Publish values to 2 different data sources
  fim=millis();
  if(inicio<fim-2000) //insere a temperatura e humidade de dois em dois segundos
  {
        client.add("temperatura", sensor_valueT); //Insert your variable Labels and the value to be sent
        client.ubidotsPublish("gabinete");
        client.add("humidade", sensor_valueH);
        client.ubidotsPublish("gabinete");
        
        inicio=millis();
  }

 //relay aquecedor 
if(sensor_valueT < 20){
  digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH     
    }

    if(sensor_valueT > 30){
  digitalWrite(relayPin, LOW); // turn on relay with voltage HIGH   
    }

 //led janela
 if(sensor_valueH > 70) {
  digitalWrite(ledPin, HIGH);
 }
 if (sensor_valueH < 60){
  digitalWrite(ledPin, LOW);
 }
 


  Serial.print(inicio);
  Serial.print("   ");
  Serial.println(fim);
  client.loop();
    
  }
  }
