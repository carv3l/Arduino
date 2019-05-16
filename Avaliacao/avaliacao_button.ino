int count = 0;
int state = 0;
int button_pin = 2;
int led_pin = 4;

bool flag = false;

int previous = LOW;
int actual = LOW;

long time = 0;         
long debounce = 0; 

void setup() {
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(button_pin),mSwitchLED, CHANGE);
}

void loop() {
  if (flag) {
    flag = false;
    state = digitalRead(button_pin);
    Serial.println(state);
    if(state == HIGH ){
      previous = actual;
      actual = HIGH;
    }
    else if(state == LOW){
      previous = actual;
      actual = LOW;
    }
    if(previous == HIGH && actual == LOW && millis() - time > debounce){    
      count++;
      time = millis();  
      digitalWrite(led_pin,count%2);
    }
  }
}

void mSwitchLED(){
  flag = true;
}  

