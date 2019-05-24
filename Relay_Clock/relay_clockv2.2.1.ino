int pino_sensor = 3;
int pino_botao =  2;
int pino_led = 4;
int pino_relay = 8;
bool flag = false;
bool flag_sensor = false;
long time_millis = 0;
long debounce = 200;
int count = 0;
volatile bool isworking = false;
int previous = LOW;
int actual = LOW;
int sensibilidade = 20000; //Se não detetar vibração é 0


void setup() {
  pinMode(pino_sensor, INPUT);
  pinMode(pino_botao, INPUT);
  pinMode(pino_led, OUTPUT);
  pinMode(pino_relay, OUTPUT);
  digitalWrite(pino_relay, HIGH);
  Serial.begin(9600);
  Serial.println("----------- Vibration demo ----------------------");
  attachInterrupt(digitalPinToInterrupt(pino_botao),mSwitchLED, RISING);
}
void loop() {
  if (millis() - time_millis > debounce) {
    if (flag) {
      delay(100);
      flag = false;
    if(isworking){
     relay(0);
    }
    count++;
    TP_init(count % 2);
    time_millis = millis();
     }
      
  }
}

void TP_init(int estado) {
  digitalWrite(pino_led , estado);
  while (flag_sensor) {
    Serial.println("Reading");
    long measurement = pulseIn(pino_sensor, HIGH); //wait for the pin to get HIGH and returns measurement
    if (measurement >= sensibilidade) {
      flag = false;
      Serial.println("-----TRIGGER:");
      relay(1);
      Serial.println(measurement);
    }
  }
}

void relay(int estado) {
// O rele de estado sólio para fazer bridge tem de estar em low, para desconectar tem de ser em high
  if(estado == 1){
   isworking = true;
     digitalWrite(pino_relay, LOW);
  }
  if(estado == 0){
   isworking = false;
     digitalWrite(pino_relay, HIGH);
  }
}
void mSwitchLED(){   
  flag = true;
  flag_sensor = !flag_sensor;
}  
