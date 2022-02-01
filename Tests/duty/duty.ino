const int pin_PWM = 3;
float DutyCycle;
float D = 200;

void setup(){
  TCCR2B = TCCR2B & B11111000 | B00000001; // change for PWM frequency of 31372.55 Hz 
  pinMode (pin_PWM,OUTPUT);
  Serial.begin(9600);
}


void loop(){
  delay (500);
  analogWrite(pin_PWM,D);
  DutyCycle = (D/255.0)*100.0;
  Serial.println(DutyCycle);
  
  
  }
