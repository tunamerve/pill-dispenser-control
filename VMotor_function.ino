#include <Wire.h> 

void setup_VMotor(){
  pinMode(VMotor_pin,OUTPUT); 
  
  Wire.onReceive(empfangeDaten_VMotor);

  Serial.println("Bereit zum Empfangen der VMotor-Daten");
}

void loop_VMotor() {
 if (VMotor_stat == 1 && VMotor_delay != 0) 
  {
    digitalWrite(VMotor_pin,HIGH);
    delay(VMotor_delay);
    VMotor_stat = 0;
  }
  else
  {
    digitalWrite(VMotor_pin,LOW); 
  }
}

void empfangeDaten_VMotor(int byteCount) {
  while (Wire.available()) {
    if (read_flag == 0)
    {
      VMotor_stat = Wire.read();
      read_flag = 1; 
      Serial.print("Status des Vibrationsmotors: ");
      Serial.println(VMotor_stat);
    }
    else
    {
      VMotor_delay = (Wire.read()*1000);
      read_flag = 0;
      Serial.print("Das Delay beträgt: "); // hier ist das Delay die Zeit, die der Vibrationsmotor vibriert 
      Serial.print(VMotor_delay);
      Serial.println(" ms"); 
    }
  }
}

void VMotor_Konstruktor(int pin) {
  VMotor_pin = pin; 
}
