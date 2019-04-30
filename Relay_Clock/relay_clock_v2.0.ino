int AUDIOPINR = 4;
int relay_pin = 2;

void setup() {
   pinMode(relay_pin, OUTPUT);
   pinMode(AUDIOPINR, INPUT);
  digitalWrite(AUDIOPINR, LOW);
  digitalWrite(relay_pin, LOW);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Start"); 
}

void loop() {
 Serial.println("LOW");
 attachInterrupt(digitalPinToInterrupt(AUDIOPINR),triggerMOTOR,RISING);
 delay(500);
}

void triggerMOTOR(){
  Serial.println("ATIVO");
  digitalWrite(relay_pin, HIGH);
  }
