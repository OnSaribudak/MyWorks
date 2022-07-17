#define relay 14


#include "DHT.h"       
#define DHTTYPE DHT11   
#define dht_dpin  D5

DHT dht(dht_dpin, DHTTYPE);
long int x = 0;
long int y ;


void setup() {
  
  dht.begin();
  pinMode(relay,OUTPUT);
  pinMode(sensor,OUTPUT);
Serial.begin(115200);
}

void loop() {
  

y = millis();
if(y-x<=10000){
  digitalWrite(relay,HIGH);
int analogdan_gelen_deger = analogRead(A0); 
Serial.print("ldr\t");
Serial.println(analogdan_gelen_deger);
  
  }
  else if (y-x>10000 && y-x<=20000){
  
digitalWrite(relay,LOW);

digitalWrite(sensor,HIGH);
int analogdan_gelen_deger2 = analogRead(A0); 
Serial.print("tpr\t");
Serial.println(analogdan_gelen_deger2);
    
    }

    else{
      digitalWrite(sensor,LOW);
      x = millis();
      }



 float nem_havadaki = dht.readHumidity();
    float sicaklik_ortamdaki = dht.readTemperature();  
     Serial.print("\t\t\t");       
    Serial.print("Havadaki Nem Oranı = ");
    Serial.print(nem_havadaki);
    Serial.print("%  ");
    Serial.print("Ortamın Sıcaklığı = ");
    Serial.print(sicaklik_ortamdaki); 
    Serial.println("C  ");



}
