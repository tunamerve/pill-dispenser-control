#include <TimerOne.h>
#include <Wire.h>

#define add 0x05


//-------EMotor------------//
#define EMotor0 26         // EMotor0 an der nicht rotierenden Scheibe (es gibt nur einen) 
#define EMotor0PWM 28      // EMotor0 (PWM-Pin) !kein PWM-Signal notwendig, da Schneckengetriebemotor bereits notwendige Übersetzung besitzt!
#define EMotor0DIR 30      // EMotor0 (DIRECTION-Pin) 0 = Drehung im Uhrzeigersinn 
 
int EMotor_pin = 22;       // default pin 
//-------end EMotor--------//


//-------SMotor------------//
#define SMotor0 40         // SMotor in Gehäuse 0 (Standby-Pin) 
#define SMotor0PWM 13      // SMotor in Gehäuse 0 (PWM-Pin)  
#define SMotor0HIGH 41     // SMotor in Gehäuse 0 (Treiber-Input-Pin AIN2 mit High-Pegel) 
#define SMotor0LOW 42      // SMotor in Gehäuse 0 (Treiber-Input-Pin AIN1 mit Low-Pegel)

#define SMotor1            // SMotor in Gehäuse 1
#define SMotor7 13         // SMotor in der Überprüfungseinheit
 
int SMotor_pin = 22;       // default pin 
int SMotor_pwm_pin = 23;   // default pwm pin 
int SMotor_high_pin = 24;  // default high pin 
int SMotor_low_pin = 25;   // default low pin 

bool SMotor_is_active = 0; 
bool SMotor_stat = 0;
int SMotor_delay = 2950;   // delay in ms, nicht ändern falls nicht sicher  
//-------end SMotor--------//


//-------VMotor------------//
#define VMotor0 50         // VMotor in Gehäuse 0
#define VMotor1 51         // VMotor in Gehäuse 1                                                                    
int VMotor_pin = 22;       // default pin 

int VMotor_delay = 0; 
bool VMotor_stat = 0;  
bool read_flag = 0; 
//-------end VMotor--------//


//-------LSensor-----------//
#define LSensor0 A15       // LSensor in Gehäuse 0  
#define LSensor1 A14       // LSensor in Gehäuse 1 
#define LSensor7 A13       // LSensor in der Überprüfungseinheit 
int LSensor_pin = 22;      // default pin 

int LSensor_val = 0; 
bool LSensor_is_active = 0; 
//-------end LSensor-------//


//-------ISensor-----------//
#define ISensor0 53        // ISensor an der nicht rotierenden Scheibe 
int ISensor_pin = 22;      // default pin 

int ISensor_val = 0; 
int ISensor_cnt = 0; 
bool ISensor_is_active = 0; 
//-------end ISensor-------//


//-------CSensor-----------//
#define S0 6
#define S1 5
#define S2 4
#define S3 3
#define OUT 2

int g_count = 0;
int g_array[3];
int g_flag = 0;
float g_SF[3];
//-------end CSensor-------//

char comp = 'S'; 
int setup_delay = 1000; 

void setup() {

Serial.begin(9600);

Wire.begin(add); 
Wire.onRequest(sendeDaten); 

//ISensor_Konstruktor(ISensor0); 

//LSensor_Konstruktor(LSensor0); 
//LSensor_Konstruktor(LSensor1); 
LSensor_Konstruktor(LSensor7); 


VMotor_Konstruktor(VMotor0); 
//VMotor_Konstruktor(VMotor1); 

EMotor_Konstruktion(EMotor0,EMotor0PWM,EMotor0DIR); 
SMotor_Konstruktor(SMotor0,SMotor0PWM,SMotor0HIGH,SMotor0LOW); //int standby_pin, int pwm_pin, int high_pin, int low_pin 
//SMotor_Konstruktor(SMotor1);
//SMotor_Konstruktor(SMotor7);

switch (comp)
  {
    case 'V': 
      Serial.println("Vibrationsmotor aktiv - Setup startet");
      delay(setup_delay);  
      setup_VMotor();
      break;  
    case 'L':
      Serial.println("Lichtsensor aktiv - Setup startet");
      delay(setup_delay); 
      setup_LSensor();
      break;  
    case 'I':
      Serial.println("Lichtschranke aktiv - Setup startet");
      delay(setup_delay);  
      setup_ISensor();
      break;  
    case 'C':
      Serial.println("Farbsensor aktiv - Setup startet");
      delay(setup_delay); 
      setup_CSensor(); 
      break; 
    case 'E':
      Serial.println("Getriebemotor aktiv - Setup startet");
      delay(5000); 
      setup_EMotor(); 
      break; 
    case 'S':
      Serial.println("Servo-Motor aktiv - Setup startet");
      delay(setup_delay); 
      setup_SMotor(); 
      break; 
    default: 
      Serial.println("Es wurde keine gültige Komponente ausgewählt.");
  }
  
} 


void loop() { 

switch (comp)
  {
    case 'V': 
      loop_VMotor(); 
      break; 
    case 'L':
      loop_LSensor();
      break;  
    case 'I':
      loop_ISensor(); 
      break; 
    case 'C':
      loop_CSensor(); 
      break; 
    case 'E': 
      loop_EMotor(); 
      break;
    case 'S': 
      loop_SMotor(); 
      break; 
    default: 
      delay(100); 
  }
  
}

void sendeDaten() {
  Wire.write(comp); 
}
