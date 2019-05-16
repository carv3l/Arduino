int pino_sensor = 3;
int pino_botao =  2;
int pino_led = 4;
int pino_relay = 8;
bool flag = true;
long time_millis = 0;
long debounce = 0;
int count = 0;
volatile bool isworking = false;
int previous = LOW;
int actual = LOW;
int sensibilidade = 8000; //Se não detetar vibração é 0


void setup() {
  pinMode(pino_sensor, INPUT);
  pinMode(pino_botao, INPUT);
  pinMode(pino_led, OUTPUT);
  pinMode(pino_relay, OUTPUT);
  digitalWrite(pino_relay, HIGH);
  Serial.begin(9600);
  Serial.println("----------- Vibration demo ----------------------");
}
void loop() {
  if (digitalRead(pino_botao) == HIGH) {
    previous = actual;
    actual = HIGH;
  } else if (digitalRead(pino_botao) == LOW) {
    previous = actual;
    actual = LOW;
  }
  if (previous == HIGH && actual == LOW && millis() - time_millis > debounce) {
    count++;
    Serial.println(isworking);
    if(isworking){
      digitalWrite(pino_relay, HIGH);
      isworking = false;
    }
     if (count % 2 == 1) {
      flag = true;
    }
    TP_init(count % 2);
    time_millis = millis();
  }
}

void TP_init(int estado) {
  digitalWrite(pino_led , estado);
  while (flag) {
    Serial.println("Reading");
    long measurement = pulseIn(pino_sensor, HIGH); //wait for the pin to get HIGH and returns measurement
    if (measurement >= sensibilidade) {
      flag = false;
      Serial.println("-----TRIGGER:");
      relay();
      Serial.println(measurement);
    }
  }
}

void relay() {
   isworking = true;
     digitalWrite(pino_relay, LOW);
     Serial.println("ON");
     delay(1000);
  

  
}
