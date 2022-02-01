//MPPT by D.A. Toapanta//

//INPUTS//
int index = 0;
int pin_PWM = 3; // D3 from Arduino
float deltaD = 3.827964205; //5% variation of the duty cycle//
float duty_cycle = 38; //25% to start the calculations
const int voltageSensor = A0;
const int currentSensor = A3;

//Variables for current sensor//
const int number_of_readings = 200;
const int current_zero = 510.635;  //calibrar
int current_reading[number_of_readings];
float current_average = current_zero;
float current_total = 0;

//Variables for voltage sensor//
float R1 = 30000.0;
float R2 = 7500.0;
int valueVoltage = 0;
float voltage_Vsensor_IN = 0.0;

//General Paramenters//
float voltage = 0.0;
float current = 0.0;
float P;

//Varaibles P&O//
float prev_P = 0.0;
float prev_V = 0.0;
float prev_I = 0.0;



void setup(){
  TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz 
  pinMode (pin_PWM,OUTPUT);
  Serial.begin(9600);
}


void loop(){

  valueVoltage = analogRead(voltageSensor);
  voltage_Vsensor_IN = (valueVoltage * 5.136599952) / 1024.0;
  prev_V = voltage_Vsensor_IN / (R2/(R1+R2));

  

  current_reading[index]=analogRead(currentSensor);
  current_total = current_total + current_reading [index];
  index = index + 1;   

  if (index >= number_of_readings){
  current_average = current_total/number_of_readings;
  current_total=0;
  index=0; 
  }
 

float current_mV = (current_average-current_zero)*4.443091366;
float prev_I = current_mV/66;

//Print Current and Voltage//
 
  Serial.print("Voltage = ");
  Serial.print(prev_V, 4);
  Serial.print("  Current = ");
  Serial.println(prev_I, 4);


//Call and print P&O method//

  P_and_O (prev_V, prev_I);
  Serial.print("Power= ");
  Serial.print(P);
  Serial.print("mW");
  Serial.println("");

  delay(500);

}


float P_and_O (float V, float I) {
  
  P = V * I * 1000;
  float deltaP = P - prev_P;
  float deltaV = V - prev_V;
  
  if (deltaP != 0 ){
  
                       if (deltaP > 0) {
  
                                               if (deltaV > 0) {
            
                                                                            if (0 <= duty_cycle && duty_cycle < 76.5592841){
                                                                                duty_cycle = duty_cycle + deltaD;      
                                                                            } 
                                                                            else { duty_cycle = 80.387248305; 
                                                                            } 
                                               }
                         
                                               else {
                                                                            if (0 <= duty_cycle && duty_cycle < 81){
                                                                               duty_cycle = duty_cycle - deltaD; 
                                                                            }
                                                                            else { duty_cycle = 76.5592841;
                                                                            }
                                               }
                       }


                       
                       else {
              
                                               if (deltaV > 0){
                          
                                                                            if (0 <= duty_cycle && duty_cycle < 81){
                                                                               duty_cycle = duty_cycle - deltaD;
                                                                            }
                                                                            else { duty_cycle = 76.5592841;
                                                                            }
                                               }
                                          
                                               else {
                                                                            if (0 <= duty_cycle && duty_cycle < 76.5592841) {
                                                                               duty_cycle = duty_cycle + deltaD;         
                                                                            }
                                                                            else { duty_cycle = 80.387248305;   
                                                                            }
      
                                               }
                       }
  }
  
  else { duty_cycle = duty_cycle; 
  }

prev_V = V;
prev_P = P;
return P;
}
