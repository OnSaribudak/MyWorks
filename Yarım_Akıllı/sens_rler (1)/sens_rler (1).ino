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
SoftwareSerial ss(34, 35); //rx tx
MPU6050 mpu6050(Wire);
Adafruit_BME280 bme;
Adafruit_INA219 ina219;


#define SEALEVELPRESSURE_HPA (1013.25)
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define buzzerPin 32
#define servoPin 13

float x = 1744;
long timer = 0;
unsigned long delayTime;

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



void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(buzzerPin, OUTPUT);

  myservo.setPeriodHertz(50);
  myservo.attach(servoPin);
  myservo.write(0);

  while (!Serial);
  unsigned status;
  status = bme.begin();

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    while (1) delay(10);
  }


  uint32_t currentFrequency;


  if (! ina219.begin()) {
    while (1) {
      delay(10);
    }
  }

}

float flat, flon;
unsigned long age;
int year;
byte month, day, hour, minute, second, hundredths;
unsigned long age2;
int alt = gps.f_altitude();
float busvoltage = 0;

void loop() {
  smartdelay(10);
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
  gps.f_get_position(&flat, &flon, &age);
  busvoltage = ina219.getBusVoltage_V();
  mpu6050.update();
  
  EkranaYazdirma();

  if (bme.readAltitude(SEALEVELPRESSURE_HPA) - x >= YonDegisimi)
  {
    Asagi = true;
  }
  Buzzer((bme.readAltitude(SEALEVELPRESSURE_HPA) - x));
  Ayrilma(bme.readAltitude(SEALEVELPRESSURE_HPA) - x);
}


static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do {
    while (ss.available())
      gps.encode(ss.read());
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

void MpuYazdir ()
{ 
  
  Serial.print(mpu6050.getAngleX());
  Serial.print("/");
  Serial.print(mpu6050.getAngleY());
  Serial.print("/");
  Serial.print(mpu6050.getAngleZ());
  Serial.print("/");
}

void BmeYazdir ()
{ 
  Serial.print(bme.readTemperature());       //bme280 sıcaklık verisi
  Serial.print("/");
  Serial.print(bme.readPressure() / 100.0F);   // bme280 basınç verisi
  Serial.print("/");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA) - x);  //bme280 zeminden yükseklik verisi
  Serial.print("/");
}

void GpsYazdir ()
{ 
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


void HizYazdir ()
{                         
  Serial.print(HizHesapla()); //model uydu hız verisi
  Serial.print("/");
}

void VoltYazdir ()
{ 
  Serial.print(busvoltage);                     // batarya voltajı
  Serial.println("");
}
void EkranaYazdirma()
{
  if (millis() - timer > 1000) {
    MpuYazdir();
    BmeYazdir();
    GpsYazdir();
    HizYazdir();
    VoltYazdir();

    timer = millis();
  }
}
