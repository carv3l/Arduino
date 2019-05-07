int ledPin1=1;
int ledPin2=2;
int ledPin3=3;
int ledPin4=4;
int ledPin5=5;
int ledPin6=6;
int ledPin7=7;
int ledPin8=8;

void setup() {
pinMode(ledPin1,OUTPUT);
pinMode(ledPin2,OUTPUT);
pinMode(ledPin3,OUTPUT);
pinMode(ledPin4,OUTPUT);
pinMode(ledPin5,OUTPUT);
pinMode(ledPin6,OUTPUT);
pinMode(ledPin7,OUTPUT);
pinMode(ledPin8,OUTPUT);
}

void loop() {

for (int i=8; i >= 1; i--){
      digitalWrite(i,HIGH);
      delay(500);
      digitalWrite(i,LOW);
   }
}
