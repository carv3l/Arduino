int count = 0;
int state = 0;
int button_pin = 2;
int led_pin = 4;

int previous = LOW;
int actual = LOW;

long time = 0;         
long debounce = 0; 

void setup() {
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(button_pin);
  if(state == HIGH){
    previous = actual;
    actual = HIGH;
  }
  else if(state == LOW){
    previous = actual;
    actual = LOW;
  }
  if(previous == HIGH && actual == LOW && millis() - time > debounce){    
    time = millis();  
  }

  Serial.println(number,count);
}
