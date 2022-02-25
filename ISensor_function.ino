#include <Wire.h>

void  setup_ISensor() {  
pinMode(ISensor_pin,INPUT); 

Wire.onRequest(sendeDaten_ISensor); 

Serial.println("Bereit für Übertragung der ISensor-Daten"); 
} 

void loop_ISensor() { 
ISensor_val = digitalRead(ISensor_pin); 
  if (ISensor_val == HIGH)
  {
    if (ISensor_cnt = 10) 
    {
     Serial.println(ISensor_val); 
     ISensor_cnt = 0;  
     ISensor_is_active = 1; 
    }
    else
    {
     ISensor_cnt += 1;    
    }
  }
  else 
  {
    ISensor_cnt = 0; 
  }
delay(500);  
}

void sendeDaten_ISensor() {
  if(ISensor_is_active == 1){Wire.write(1);}
}

void ISensor_Konstruktor(int pin){
  ISensor_pin = pin; 
}
