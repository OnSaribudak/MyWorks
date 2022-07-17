#include "DHT.h"       
#define DHTTYPE DHT11   
#define dht_dpin  9 
const int relay = 14;

DHT dht(dht_dpin, DHTTYPE); 
void setup(void)
{ 
  pinMode(relay, OUTPUT);
  dht.begin();
  Serial.begin(115200);
}
void loop() {
    float nem_havadaki = dht.readHumidity();
    float sicaklik_ortamdaki = dht.readTemperature();  
    Serial.print("\t\t\t");       
    Serial.print("Havadaki Nem Oranı = ");
    Serial.print(nem_havadaki);
    Serial.print("%  ");
    Serial.print("Ortamın Sıcaklığı = ");
    Serial.print(sicaklik_ortamdaki); 
    Serial.println("C  ");
    if (sicaklik_ortamdaki >=28 ){
      digitalWrite(relay,HIGH);
    }
    else {
      digitalWrite(relay,LOW);

      }
    }
    
    
 
  
