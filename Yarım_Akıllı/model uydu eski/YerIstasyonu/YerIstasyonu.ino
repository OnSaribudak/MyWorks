#include <esp_now.h>
#include <WiFi.h>

#include "ModelUyduVeriler.h"

uint8_t broadcastAddress[] = {0xF4, 0xCF, 0xA2, 0x98, 0x11, 0x98}; // F4:CF:A2:98:11:98  Yer İstasyonu

ModelUyduVeriler veriler;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //esp_now_register_send_cb(VeriGonderici);
  
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
       
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
    esp_now_register_recv_cb(VeriAlici);
}
 
void loop() {
  GonderilecekVerileriDuzenle(&veriler);
  
//  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &veriler, sizeof(veriler));
//   
//  if (result == ESP_OK) { Serial.println("Sent with success");}
//  else { Serial.println("Error sending the data");}
  //delay(1000);
}
void VeriGonderici(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void VeriAlici(const uint8_t * mac,  uint8_t *incomingData, int len) 
{
  memcpy(&veriler, incomingData, sizeof(veriler));
  AlinanVerileriEkranaYazdir(veriler);
}

void AlinanVerileriEkranaYazdir(ModelUyduVeriler veriler )
{
 Serial.print(veriler.sayac);
 Serial.print("/");
 Serial.print(veriler.flat);
 Serial.print("/");
 Serial.print(veriler.flon);
 Serial.print("/");
 Serial.print(veriler.alti);
 Serial.print("/");
 Serial.print(veriler.year);
 Serial.print("/");
 Serial.print(veriler.month);
 Serial.print("/");
 Serial.print(veriler.day);
 Serial.print("/");
 Serial.print(veriler.hour);
 Serial.print("/");
 Serial.print(veriler.minute);
 Serial.print("/");
 Serial.print(veriler.second);
 Serial.print("/");
 Serial.print(veriler.x);
 Serial.print("/");
 Serial.print(veriler.y);
 Serial.print("/");
 Serial.print(veriler.z);
 Serial.print("/");
 Serial.print(veriler.temp);
 Serial.print("/");
 Serial.print(veriler.press);
 Serial.print("/");
 Serial.print(veriler.bmeAlti);
 Serial.print("/");
 Serial.print(veriler.speed);
 Serial.print("/");
 Serial.print(veriler.voltage);
 Serial.println("/");
}

void GonderilecekVerileriDuzenle(ModelUyduVeriler *veriler)
{
  
}
