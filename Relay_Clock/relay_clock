//Definir as portas do audio direito e esquerdo, os pinos sao analogicos
#define AUDIOPINR 2
#define AUDIOPINL 4

bool valR = 0;
bool valL= 0;
int IN_PIN = 2;

void setup() {
  pinMode(IN_PIN, OUTPUT);
  digitalWrite(IN_PIN, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start"); 
}
void loop() {
  
valR = analogRead(AUDIOPINR)>0;
Serial.print("Right ");
Serial.println(valR); 
valL = analogRead(AUDIOPINL)>0;
Serial.print("Left ");
Serial.println(valL);
digitalWrite(IN_PIN, valR || valL ? HIGH : LOW);
delay(300);
}
