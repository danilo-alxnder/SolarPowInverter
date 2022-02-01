
int temp=0;
float sum=0;
float AMPS_SCALE = 0;
float amps=0;
void setup (){
  Serial.begin (9600);
}

void loop (){
  for (int i= 0; i <100; i++){
    temp=analogRead(A0);
    sum+= temp;
    delayMicroseconds (50);
  }
  sum=sum/100;
}

 AMP_SCALE= 5/(1024*0.66);
 amps = AMP_SCALE* sum - 3.787878787878788;

 Serial.print(amps);
 delay(500); 
 }
