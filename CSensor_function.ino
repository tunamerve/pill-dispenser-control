#include <TimerOne.h>
#include <Wire.h>

void TSC_Init()
{
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(OUT, INPUT);
 digitalWrite(S0, LOW);
 digitalWrite(S1, HIGH);
}

void TSC_FilterColor(int Level01, int Level02)
{
 if(Level01 != 0)
 Level01 = HIGH;
 if(Level02 != 0)
 Level02 = HIGH;
 digitalWrite(S2, Level01);
 digitalWrite(S3, Level02);
}

void TSC_Count()
{
 g_count ++ ;
}

void TSC_Callback()
{
 switch(g_flag)
 {
 case 0:
 Serial.println("->WB Start");
 TSC_WB(LOW, LOW); //Filter ohne Rot
 break;
 case 1:
 Serial.print("->Frequency R=");
 Serial.println(g_count);
 g_array[0] = g_count;
 TSC_WB(HIGH, HIGH); //Filter ohne Grün
 break;
 case 2:
 Serial.print("->Frequency G=");
 Serial.println(g_count);
 g_array[1] = g_count;
 TSC_WB(LOW, HIGH); //Filter ohne Blau
 break;
 case 3:
 Serial.print("->Frequency B=");
 Serial.println(g_count);
 Serial.println("->WB End");
 g_array[2] = g_count;
 TSC_WB(HIGH, LOW); //Kein Filter 
 break;
 default:
 g_count = 0;
 break;
 }
}
void TSC_WB(int Level0, int Level1) //Weißabgleich
{
 g_count = 0;
 g_flag ++;
 TSC_FilterColor(Level0, Level1);
 Timer1.setPeriod(1000000);
}

void setup_CSensor()
{
 TSC_Init();

 Timer1.initialize();
 Timer1.attachInterrupt(TSC_Callback); 
 attachInterrupt(0, TSC_Count, RISING); 
 delay(4000);
 for(int i=0; i<3; i++)
 Serial.println(g_array[i]);
 g_SF[0] = 255.0/ g_array[0]; //R-Wert
 g_SF[1] = 255.0/ g_array[1] ; //G-Wert
 g_SF[2] = 255.0/ g_array[2] ; //B-Wert
 Serial.println(g_SF[0]);
 Serial.println(g_SF[1]);
 Serial.println(g_SF[2]);

 Wire.onRequest(sendeDaten_CSensor); 
 Serial.println("Übertragung der CSensor-Daten beginnt"); 
 
}
int val = 0; 
bool loop_flag = 0;

void loop_CSensor()
{
 if(loop_flag == 0)
 {
   g_flag = 0;
   for(int i=0; i<3; i++)
   {
    val = int(g_array[i] * g_SF[i]);
    Serial.println("Farbwert wird gesendet: "); 
    Serial.println(val);
   }
   delay(4000);
   loop_flag = 0; 
 }
} 

//int val_f[] = {0,0,0}; 

void sendeDaten_CSensor() { //richtige Übertragung regeln (29.11.2021)

/*    for(int i=0; i<3; i++)
   {
    val_f[i] = int(g_array[i] * g_SF[i]);
   }
   Wire.write(val_f[0]);
   Serial.println(val_f[0]); 
   Wire.write(val_f[1]);
   Serial.println(val_f[1]);
   Wire.write(val_f[2]);
   Serial.println(val_f[2]);
*/ 
}
