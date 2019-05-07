int count = 0;
int state = 0;

int previous = LOW;
int actual = LOW;

long time = 0;         
long debounce = 0; 

float number = 3.333333333;

void setup() {
  pinMode(2,INPUT);
  Serial.begin(9600);
}

void loop() {
  state = digitalRead(2);
  //delay(500);
  if(state == HIGH){
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
  }

  if(count == 9){
    count = 0;
  }

  Serial.println(number,count);
  
  /*Serial.print(count);
  Serial.print(" >> BIN: "); 
  Serial.print(count, BIN);
  Serial.print(", HEX: "); 
  Serial.print(count, HEX);
  Serial.print(", OCT: "); 
  Serial.println(count, OCT);*/

  //Serial.println((String)count + " >> BIN:" + (count,BIN));
  //Serial.println((String) "Hex: "+count, HEX);
  //Serial.println((String) "Oct: "+count, OCT);
}
