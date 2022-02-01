//voltage sensor//

const int voltageSensor = A1;

float voltage = 0.0;
int valueVoltage = 0;
float voltage_Vsensor_IN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float V = 0.0;

void setup(){
  Serial.begin(9600);
}


void loop(){

  valueVoltage = analogRead(voltageSensor);
  voltage_Vsensor_IN = (valueVoltage * 5.156742494) / 1023.0; //antiguo 5.164899552
  voltage = voltage_Vsensor_IN / (R2/(R1+R2));
  V= voltage;
  
  Serial.println(" V");
  Serial.print(V, 4);

  delay(1000);

}



  
