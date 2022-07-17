#include <espnow.h>
#include <ESP8266WiFi.h>

#include "DHT.h"
//#include"Send_Data.h"

#define DHTTYPE DHT11
#define dht_pin  9
#define soil_pin  A0


DHT dht(dht_pin, DHTTYPE);
//Send_Data Data_of_Kit1;
uint8_t  broadcastAddress[] = {0x3C, 0x61, 0x05, 0xD0, 0x61, 0x2B}; // 3C:61:05:D0:61:2B


void setup()
{
  Serial.begin(115200);
  dht.begin();
  Esp_Setting();


}

void loop()
{

 // Send_Data_Design(&Data_of_Kit1);
  //Print_Screen();

}


//void Send_Data_Design (Send_Data *Data_of_Kit1)
//{
//  Data_of_Kit1->temp = dht.readTemperature();
//  Data_of_Kit1->hum = dht.readHumidity();
//  Data_of_Kit1->hum_of_soil = analogRead(soil_pin);
//
//  esp_now_send(broadcastAddress, (uint8_t *) &Data_of_Kit1, sizeof(Data_of_Kit1));
//}

void On_Data_Sent(uint8_t *mac_addr, uint8_t sendStatus)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail");
}

void Esp_Setting()
{
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(On_Data_Sent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

//void Print_Screen()
//{
//  Serial.println(temp = dht.readTemperature());
//  Serial.println(hum = dht.readHumidity());
//  Serial.println(hum_of_soil= analogRead(soil_pin));
//  delay(500);
//}
