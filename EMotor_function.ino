#include<Wire.h>


void setup_EMotor() {

Serial.println("Bereit für Übertragung der ISensor-Daten"); 

pinMode(EMotor_pin,OUTPUT); 
pinMode(EMotor_pwm_pin,OUTPUT); 
pinMode(EMotor_dir_pin,OUTPUT); 
  
}


void loop_EMotor() {

//digitalWrite(EMotor,HIGH);  
}


void EMotor_Konstruktor(int output_pin, int pwm_pin, int dir_pin){
  EMotor_pin = pin; 
  EMotor_pwm_pin = pwm_pin; 
  EMotor_dir_pin = dir_pin; 
  
}
