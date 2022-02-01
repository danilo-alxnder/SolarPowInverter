int period = 5000;
unsigned long time_now = 0;
 
void setup() {
    Serial.begin(9600);
}
 
void loop() {
    if(millis() > time_now + period){
        time_now = millis();
        Serial.println("Hello");
        
    }
   
    //Run other code
}
