//Both sensors working//

//Current sensor variables//
float Sensibilidad = 0.1729997;

//Voltage sensor variables//
const int voltageSensor = A1;
float voltage_Vsensor_IN = 0.0;
int valueVoltage = 0;
float voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;

//P&O// variables//
float prev_V = 0.0;
float prev_I = 0.0;

void setup(){
  Serial.begin(9600);
}


void loop(){

  prev_I = get_corriente(2000); //obtenemos la corriente promedio de 500 muestras 

  valueVoltage = analogRead(voltageSensor);
  voltage_Vsensor_IN = (valueVoltage * 5.156742494) / 1023.0; //antiguo 5.164899552
  voltage = voltage_Vsensor_IN / (R2/(R1+R2));
  prev_V = voltage;
  
//Print Current Voltage and Power //
 
  Serial.print("Voltage = ");
  Serial.print(prev_V, 4);
  Serial.println("   Current = ");
  Serial.print(prev_I, 4);

  delay(1500);

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





  
