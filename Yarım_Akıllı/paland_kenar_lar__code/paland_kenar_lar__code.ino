#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define ONE_WIRE_BUS 7
#define mikrofon_pin A0
#define DHTPIN 2 
#define DHTTYPE DHT11 
int mikrofon ;


DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer;

void setup(void)
{
  Serial.begin(9600);
   dht.begin();

  
  sensors.begin();
if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); 





  sensors.setResolution(insideThermometer, 9);

}


void loop(void)
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("NEM: ");
  Serial.println(h);
  Serial.print("ORTAMIN SICAKLIK: ");
  Serial.println(t);
 
  sensors.requestTemperatures();
  microfon_read();
  printTemperature(insideThermometer); 
  delay(100);
}



void printTemperature(DeviceAddress deviceAddress)
{

  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.println(tempC);
}

void microfon_read(){
  
  mikrofon = analogRead(mikrofon_pin);
  Serial.print("Mikrofon : ");
  Serial.println(mikrofon);
  mikrofon >800?delay(5000):delay(100);
  
  }
