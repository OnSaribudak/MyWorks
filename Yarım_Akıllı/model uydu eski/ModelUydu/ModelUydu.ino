#include <esp_now.h>
#include <WiFi.h>

#include "Sensorler.h"
#include "ModelUyduVeriler.h"
#include "Veriler.h"

uint8_t broadcastAddress[] = {0x08, 0x3A, 0xF2, 0xA6, 0x99, 0xD4}; // 08:3A:F2:A6:99:D4  Model uydu

ModelUyduVeriler veriler;

void setup() 
{
  Serial.begin(115200);
  EspSetup();
  SensorlerSetup();
}

void loop() {
  GonderilecekVerileriDuzenle(&veriler);
  EspLoop();  
  SensorlerLoop();
  if(SayacBasla) Sayac();  
}

void EspSetup()
{ 
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK){ Serial.println("Error initializing ESP-NOW"); return;}
  
  esp_now_register_send_cb(VeriGonderici);//
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){ Serial.println("Failed to add peer");return;}
  
  esp_now_register_recv_cb(VeriAlici);
}

void EspLoop()
{
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &veriler, sizeof(veriler));
  if (result == ESP_OK) { Serial.println("Sent with success");}
  else { Serial.println("Error sending the data"); }
}

void SensorlerSetup()
{
  ss.begin(9600);
  Wire.begin();
  Wire.begin(I2C_SDA, I2C_SCL);

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

  if (! ina219.begin()) {
    while (1) {
      Serial.print("SensorID was: 0x");
    }
  }
}

void SensorlerLoop()
{
  mpu6050.update();
  smartdelay(1000);
  
  gps.f_get_position(&flat, &flon, &age);
  alt = gps.f_altitude();
  
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
  busvoltage = ina219.getBusVoltage_V();

  if (bme.readAltitude(SEALEVELPRESSURE_HPA) - x >= YonDegisimi)
  {
    Asagi = true;
  }
  Buzzer((bme.readAltitude(SEALEVELPRESSURE_HPA) - x));
  Ayrilma(bme.readAltitude(SEALEVELPRESSURE_HPA) - x);
}

void VeriAlici(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  memcpy(&veriler, incomingData, sizeof(veriler));
  AlinanVerileriEkranaYazdir(veriler);
}

void VeriGonderici(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
