int LED_Pin = 6;
int vibr_Pin =3;
bool sinal = false;
long tempo_millis = 0; 
int periodo = 3000; 

void setup(){
  pinMode(LED_Pin, OUTPUT);
  pinMode(vibr_Pin, INPUT); //set vibr_Pin input for measurment
  //time = millis();
  Serial.begin(9600); //init serial 9600
  Serial.println("----------------------Vibration demo------------------------");
}
void loop(){
  tempo_millis = millis();
  int sensor_values[10];
  long measurement = TP_init();
  delay(100);
  Serial.println(measurement);

   if (sinal == true){    
      for(int i = 0;i<=10;i++){
        sensor_values[i] = measurement;
        }
  
 for(int i = 0;i<10;i++){
  if(sensor_values[i] != 0 && sensor_values[i+1] != 0){
  int soma = sensor_values[i] + sensor_values[i+1];  
  Serial.println((String)"SOMA: " +soma);
  if(soma <= 10){
    vibrar(true);
    } else {
      vibrar(false);
      }
    }
  }
        
 }
  if(measurement > 10000){
    sinal=true;
    }
}




//FUNÇÃO PARA TRATAR O SINAL COMO PWM
long TP_init(){
  delay(100);
  long measurement=pulseIn(vibr_Pin, HIGH);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}

void vibrar(bool state){    
if(state){
digitalWrite(LED_Pin, HIGH);
//Serial.println("ACESO");
while(millis() < tempo_millis + periodo){
  // esperar 3 segundos ou seja fica a vibrar por 3 segundos
        digitalWrite(LED_Pin, LOW);
    }
}else{
  digitalWrite(LED_Pin, LOW);
  Serial.println("OFF");
  Serial.println((String)"TEMPO:"+tempo_millis);
  
  }
  }


int detector(){
  
  
  
  }








