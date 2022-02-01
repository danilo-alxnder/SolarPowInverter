//current sensor//

int index = 0;
const int number_of_readings = 200;
const int current_zero = 510.635;  //calibrar
int current_reading[number_of_readings];
float current_average = current_zero;
float current_total = 0;

void setup (){
  Serial.begin (9600);
}

void loop (){
  
  current_reading[index]=analogRead(A1);
  current_total = current_total + current_reading [index];
  index= index + 1;   

  if (index >= number_of_readings){
  current_average= current_total/number_of_readings;
  
  Serial.print ("Current average=");
  Serial.println(current_average);
  current_total=0;
  index=0; 
  } 


}
  
  
 
