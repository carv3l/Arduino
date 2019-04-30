#define AUDIOPINR 2
#define AUDIOPINL 4

int valR = 0;
int valL= 0;
int IN_PIN = 2;
void setup() {
  pinMode(IN_PIN, OUTPUT);
  digitalWrite(IN_PIN, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Enter 1 to turn on lamp, 0 to turn off"); 
}
void loop() {
valR = analogRead(AUDIOPINR);
Serial.print("Right");
Serial.println(valR); 
valL= analogRead(AUDIOPINL);
Serial.print("Left");
Serial.println(valL);

if(valR != 0 && valL != 0){
 digitalWrite(IN_PIN, HIGH);
}
if(valR == 0 && valL == 0){
 digitalWrite(IN_PIN, LOW);
}
delay(300);
  }
