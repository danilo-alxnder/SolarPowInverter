#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

byte lightning[8] = {
  B00001,
  B00110,
  B01100,  
  B11111,
  B00011,
  B00110,
  B01100,
};

int index = 0;
const int number_of_readings = 200;
const int current_zero = 510.635; //calibrar
int current_reading[number_of_readings];
int voltage_reading[number_of_readings];


float R1=30000;
float R2=7500;
float current_average = current_zero;
float current_total = 0;
float voltage_average = 0;
float voltage_total = 0;

void setup (){
  lcd.begin (16,2);
  lcd.createChar(6,lightning);
  Serial.begin (9600);

  lcd.setCursor(0,0);
  lcd.print(" ");
  lcd.print("Power Meter");
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print("D.A. Toapanta");
  delay (500);
  lcd.clear();
  }

void loop (){
  voltage_reading[index]=analogRead(A0);
  voltage_total = voltage_total + voltage_reading [index];
  current_reading[index]=analogRead(A3);
  current_total = current_total + current_reading [index];
  index=index + 1;   

  if (index >= number_of_readings){
  current_average= current_total/number_of_readings;
  voltage_average= voltage_total/number_of_readings;
  Serial.print ("Current average=");
  Serial.print(current_average, 3);
  Serial.print ("  Voltage average=");
  Serial.println(voltage_average, 3);
  current_total=0;
  voltage_total=0; 
  index=0; 
  } 

float voltage = ((5*(voltage_average)*(R1+R2))/(1023*R2));
float current_mV = (current_average-current_zero)*4443.091366;
float current = current_mV/66;
float power = (voltage*current); 

  
lcd.clear();
lcd.setCursor(0,0);
lcd.print(voltage, 3);
lcd.print("V");

lcd.print(" ");
Serial.println(current, 3);
lcd.print("A");

lcd.setCursor (0,1);
lcd.print(power, 3);
lcd.print("W");
delay (1);
}
  
  
  
  
