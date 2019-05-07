int botao=8;
 int led=9;
 int estadoBotao =0;
 int estadoled =0;
 

void setup() {
  pinMode(led,OUTPUT);
  pinMode (botao,INPUT);
  Serial.begin(9600);
   
}

void loop() {
  estadoBotao = digitalRead(botao);
  Serial.println(estadoBotao);
  delay(500);
  if (estadoBotao==HIGH){
    if(estadoled == 0){
    digitalWrite(led,HIGH);
    estadoled=1;    
    Serial.println("ON");
    }else {
      digitalWrite(led,LOW);
      estadoled=0;
      Serial.println("OFF");
      }
  }


  }
