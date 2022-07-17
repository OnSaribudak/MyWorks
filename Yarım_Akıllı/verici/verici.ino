
#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct test_struct {
  int analogdan_gelen_deger ;
 
  float nem_havadaki;
  float sicaklik_ortamdaki;

} test_struct;

// Create a struct_message called myData
test_struct myData;



// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("tpr: ");
  Serial.println(myData.analogdan_gelen_deger);

}







void setup() {

   Serial.begin(115200);
  
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  // put your main code here, to run repeatedly:

}
