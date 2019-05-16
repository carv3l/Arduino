int count = 0;
int button_pin = 2;
int led_pin = 4;
bool flag = false;
long timemillis = 0;         
long debounce = 200; 

long current = 0;

void setup() {
  pinMode(button_pin, INPUT);
  pinMode(led_pin,OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(button_pin),mSwitchLED, RISING);
}

void loop() {
  current = millis() - timemillis;
  if(current > debounce){
  
      if (flag) {
         flag = false;
         Serial.println(current);
      count++;
      Serial.println(count); 
      digitalWrite(led_pin,count%2);           
      }
            
      timemillis = millis();
  }
}

void mSwitchLED(){   
  flag = true;
}  

