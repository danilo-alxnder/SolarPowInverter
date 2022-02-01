
//INPUTS//
  int pin_PWM = 3; // D3 from Arduino
  const int voltageSensor = A1;
  const int voltageSensor2 = A2;
  const int currentSensor = A0;

//Variables for current sensor//
  float Sensibilidad = 0.1729997; // 0.190936036// 0.17207207

//Variables for voltage sensor//
  float voltage = 0.0;
  int valueVoltage = 0;
  float R1 = 30000.0;
  float R2 = 7500.0;
 
  //Variables for voltage sensor 2//
  #define NUM_SAMPLES 10

   int sum = 0;                    // sum of samples take
  unsigned char sample_count = 0; // current sample number
  float voltage2 = 0.0;            // calculated voltage

//Varaibles P&O//
  float P;  float voltage_Vsensor_IN = 0.0;

  float deltaD = 3; //5% variation of the duty cycle//
  float duty_cycle = 16; //25% to start the calculations
  float prev_P = 0.0;
  float prev_V = 0.0;
  float prev_I = 0.0;

void setup(){
  TCCR2B = TCCR2B & B11111000 | B00000001; // change for PWM frequency of 31372.55 Hz 
  pinMode (pin_PWM,OUTPUT);
  Serial.begin(9600);
}


void loop(){

  analogWrite(pin_PWM, duty_cycle);
  float prev_I = get_corriente(2000);  //get corriente promedio de 500 muestras 

  valueVoltage = analogRead(voltageSensor);
  voltage_Vsensor_IN = (valueVoltage * 5.129142494 )/1023.0; //FINAL 5.113142494 // 1023.0; //5.156742494 antiguo 5.164899552
  voltage = voltage_Vsensor_IN / (R2/(R1+R2)); 
  prev_V = voltage;

 
 // Voltage 2
  while (sample_count < NUM_SAMPLES) {
        sum += analogRead(A2);
        sample_count++;
  }
  voltage2 = ( ((float)sum / (float)NUM_SAMPLES * 5.114665586) / 1024.0)* 10.998;
  
 //Print Current Voltage and Power //
 
  Serial.print("Voltage = ");
  Serial.print(prev_V, 4);
  Serial.print("   Current = ");
 Serial.print(prev_I, 4);
    Serial.print("Voltage2 = ");
  Serial.println(voltage2, 4);

  P_and_O (prev_V, prev_I);
  Serial.print("   Power= ");
  Serial.print(P);
  Serial.print("mW");
  Serial.println("");
  Serial.println("");
  Serial.println("duty cycle =");
  Serial.print(duty_cycle);

   sample_count = 0;
   sum = 0;
  
  delay(50);

}

float get_corriente(int n_muestras){
  
  float voltajeSensor;
  float corriente=0;
  
  for(int i=0;i<n_muestras;i++){
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);                //lectura del sensor
    corriente = corriente+ (voltajeSensor- 2.5075)/Sensibilidad;    //Ecuación  para obtener la corriente
  }
  
  corriente= corriente/n_muestras;
  
  if(corriente > 0){
    return(corriente);
  }
  else { return(0);
       }
 
}


float P_and_O (float V, float I) {
  
  P = V * I * 1000;
  float deltaP = P - prev_P;
  float deltaV = V - prev_V;
  
  if (deltaP != 0 ){
  
                       if (deltaP > 0) {
  
                                               if (deltaV > 0) {
            
                                                                            if (0 <= duty_cycle && duty_cycle < 64){
                                                                                duty_cycle = duty_cycle + deltaD;      
                                                                            } 
                                                                            else { duty_cycle = 67; 
                                                                            } 
                                               }
                         
                                               else {
                                                                            if (0 <= duty_cycle && duty_cycle < 68){
                                                                               duty_cycle = duty_cycle - deltaD; 
                                                                            }
                                                                            else { duty_cycle = 64;
                                                                            }
                                               }
                       }


                       
                       else {
              
                                               if (deltaV > 0){
                          
                                                                            if (0 <= duty_cycle && duty_cycle < 68){
                                                                               duty_cycle = duty_cycle - deltaD;
                                                                            }
                                                                            else { duty_cycle = 64;
                                                                            }
                                               }
                                          
                                               else {
                                                                            if (0 <= duty_cycle && duty_cycle < 64) {
                                                                               duty_cycle = duty_cycle + deltaD;         
                                                                            }
                                                                            else { duty_cycle = 67;   
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
