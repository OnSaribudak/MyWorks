#include <TinyGPS.h>
#include <MPU6050_tockn.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP32Servo.h>
#include <Adafruit_INA219.h>

Servo myservo;
TinyGPS gps;
SoftwareSerial ss(16, 4); //rx tx
MPU6050 mpu6050(Wire);
Adafruit_BME280 bme;
Adafruit_INA219 ina219;

#define SEALEVELPRESSURE_HPA (1013.25)
#define servoPin 14
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define buzzerPin 12
//#define rolePin 17
#define I2C_SDA 15
#define I2C_SCL 13

int x = 0;
//long timer = 0;
unsigned long sayac = 0;
unsigned long delayTime;
bool SayacBasla = true;

float busvoltage = 0;

bool Asagi = false;
int AyrilmaYuksekligi = 400;
int YonDegisimi = 500;
int BuzzerYuksekligi = 20;

float AnlikYukseklik;
float EskiYukseklik = 0;
float Hiz;

//float AyrilmaYuksekligi =1;
//float YonDegisimi = 1.5;
//float BuzzerYuksekligi = 1;

float flat, flon;
unsigned long age;
int alt;
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long age2;

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do {
    while (ss.available())
    {
      gps.encode(ss.read());
    }
  } while (millis() - start < ms);
}

float HizHesapla()
{
  AnlikYukseklik = (bme.readAltitude(SEALEVELPRESSURE_HPA) - x);
  Hiz = abs(EskiYukseklik - AnlikYukseklik);
  EskiYukseklik = AnlikYukseklik;
  return Hiz;
}

void Buzzer (float deger)
{
  if (Asagi)
  {
    if (deger <= BuzzerYuksekligi)
    {
      digitalWrite(buzzerPin, HIGH);
    }
    else
    {
      digitalWrite(buzzerPin, LOW);
    }
  }
}

void Ayrilma(float yukseklik)
{
  if (Asagi)
  {
    if (yukseklik <= AyrilmaYuksekligi)
    {
      myservo.write(180);
      //delay(1000);
      //myservo.detach(); // Servoyu Pasif Duruma Getirme
    }
  }
}
void SisServo()
{
  if (AnlikYukseklik <= 200)
  {
    myservo.write(180);
  }
}

void MpuYazdir ()
{
  Serial.print((int)mpu6050.getAngleX());
  Serial.print("/");
  Serial.print((int)mpu6050.getAngleY());
  Serial.print("/");
  Serial.print((int)mpu6050.getAngleZ());
  Serial.print("/");
}

void BmeYazdir ()
{
  Serial.print((int)bme.readTemperature());       //bme280 sıcaklık verisi
  Serial.print("/");
  Serial.print((int)(bme.readPressure() / 100.0F));   // bme280 basınç verisi
  Serial.print("/");
  Serial.print((int)bme.readAltitude(SEALEVELPRESSURE_HPA) - x);  //bme280 zeminden yükseklik verisi
  Serial.print("/");
}

void HizYazdir ()
{
  Serial.print((int)HizHesapla()); //model uydu hız verisi
  Serial.print("/");
}

void VoltYazdir ()
{
  Serial.print((int)busvoltage);                     // batarya voltajı
  Serial.println("");
}

void Sayac()
{
  if (millis() - sayac >= 1000)
  {
    Serial.println(sayac / 1000);
    //1 Saniye sonra yapılması istenen işlemler buraya gelecek
    sayac = millis();
  }
}

void GpsYazdir ()
{
  Serial.print(sayac/1000);
  Serial.print("/");
  Serial.print(flat, 6);    // gps enlem verisi
  Serial.print("/");
  Serial.print(flon, 6);    // gps boylam verisi
  Serial.print("/");
  Serial.print(alt);      // gps yükseklik verisi
  Serial.print("/");
  Serial.print(year);      // gps yıl verisi
  Serial.print("/");
  Serial.print(month);     // gps ay verisi
  Serial.print("/");
  Serial.print(day);       // gps gün verisi
  Serial.print("/");
  Serial.print(hour + 3);  // gps gps saat verisi
  Serial.print("/");
  Serial.print(minute);    // gps dakika verisi
  Serial.print("/");
  Serial.print(second);    // gps saniye verisi
  Serial.print("/");
}

//void EkranaYazdirma()
//{
//  if (millis() - timer > 1000) {
//
//
//    timer = millis();
//  }
//}
