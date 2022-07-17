#include "DHT.h"
#define DHTPIN 2  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
int trigPin = 13; 
int echoPin = 12; 

 void dht1();
 void toprakNem();
 void alarm();
 
long zaman;
long mesafe;
int buzzerPin = 6;
int notaSayisi = 8;
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notalar[] = {C, D, E, F, G, A, B, C_};

float h;
float t;
float f;

int nem=0;
int deger;
 
void genel_setup(){
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin,INPUT); 
  noTone(buzzerPin);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Serial.begin(9600); 
}
void genel_loop()
{
  dht1();
  toprakNem();
  alarm();
 
 
}
void dht1(){
 float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
}
void toprakNem(){
  deger = analogRead(nem);
   deger = map(deger,0,1023,0,100);
   Serial.print("Toprak Nem :");
   Serial.println(deger);
   delay(500);
}

void alarm(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  zaman = pulseIn(echoPin, HIGH);
  mesafe= (zaman /29.1)/2;    
  if(mesafe<=20){
    for (int i = 0; i < notaSayisi; i++)
  {
    tone(buzzerPin, notalar[i]);
    delay(500);
    noTone(buzzerPin);
    delay(20);
  }
 
  }
  Serial.print("Uzaklik ");  
  Serial.print(mesafe);
  Serial.println(" cm");  
  delay(500); 
}
