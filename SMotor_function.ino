#include <Servo.h> 

void setup_SMotor() {  
  
Wire.onReceive(empfangeDaten_SMotor);

Serial.println("Bereit zum Empfangen der SMotor-Daten"); 

pinMode(SMotor_low_pin,OUTPUT);
pinMode(SMotor_high_pin,OUTPUT);
pinMode(SMotor_pwm_pin,OUTPUT);
pinMode(SMotor_pin,OUTPUT); 

}

void loop_SMotor() {

if(SMotor_stat == 1)
 {
  analogWrite(SMotor_pwm_pin,50); 
  digitalWrite(SMotor_pin,HIGH); 
  digitalWrite(SMotor_low_pin,LOW); 
  digitalWrite(SMotor_high_pin,HIGH);

  delay(SMotor_delay);
 }

 SMotor_stat = 0;
 digitalWrite(SMotor_pin,LOW);  
}

void empfangeDaten_SMotor(int byteCount) {
  while (Wire.available()) {
      SMotor_stat = Wire.read(); 
      Serial.print("Status des Servomotors: ");
      Serial.println(SMotor_stat);
      Serial.print("Drehzeit des Servomotors in ms: "); 
      Serial.println(SMotor_delay); 
    }
}

void SMotor_Konstruktor(int standby_pin, int pwm_pin, int high_pin, int low_pin){
  SMotor_pin = standby_pin; 
  SMotor_pwm_pin = pwm_pin; 
  SMotor_high_pin = high_pin; 
  SMotor_low_pin = low_pin;
}
