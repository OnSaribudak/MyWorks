#include <ESP8266WiFi.h>
#include <espnow.h>
#include"Rec_Data.h"

Rec_Data İncoming_Dataof_Kit1 ;

void On_Data_Recv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&İncoming_Dataof_Kit1, incomingData, sizeof(İncoming_Dataof_Kit1));
  
 
  Serial.print("Temp: ");
  Serial.println(İncoming_Dataof_Kit1.temp);
  Serial.print("Int: ");
  Serial.println(İncoming_Dataof_Kit1.hum);
  Serial.print("Float: ");
  Serial.println(İncoming_Dataof_Kit1.hum_of_soil);
  Serial.println();
}
 
void setup() {
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(On_Data_Recv);
}
