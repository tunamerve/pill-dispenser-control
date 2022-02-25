#include<Wire.h>



void setup_LSensor() {
pinMode(LSensor_pin,INPUT); 

Wire.onRequest(sendeDaten_LSensor);

Serial.println("Bereit für Übertragung der LSensor-Daten"); 

}


void loop_LSensor() {

LSensor_val = analogRead(LSensor_pin);
  
  if (LSensor_val <= 650)
  {
    Serial.println(LSensor_val); 
    LSensor_is_active = 1; 
  }
  else 
  LSensor_is_active = 0; 
}

void sendeDaten_LSensor(){
  Wire.write(LSensor_is_active); 
 
}

void LSensor_Konstruktor(int pin) {
  LSensor_pin = pin;
}
