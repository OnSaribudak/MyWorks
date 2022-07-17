//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>


float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;

 



void Ph_Setup() 
{
  
 Serial.begin(112500);
  pinMode(16,OUTPUT);
 

}
void Ph_Loop() {

digitalWrite(16,HIGH);

 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*3.3/1024/6; 
  ph_act = -5.70 * volt + calibration_value;

 Serial.print("pH Val: ");
 Serial.println(ph_act);
 delay(1000);
}
