int shockPin = 2; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement
int IN_PIN = 3;
void setup() {
  pinMode(IN_PIN, OUTPUT);
  pinMode (shockPin, INPUT) ;
  digitalWrite(IN_PIN, LOW);
  Serial.begin(9600);
  Serial.println("Enter 1 to turn on lamp, 0 to turn off"); 
}
void loop() {
shockVal = digitalRead (shockPin) ; // read the value from our sensor
  Serial.println(shockVal);
  
 //digitalWrite(IN_PIN, HIGH);

delay(1000);
 //digitalWrite(IN_PIN, LOW);
  }
