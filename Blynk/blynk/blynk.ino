#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include "ec.h"
#include "genelKod.h"
#include "serve_su_seviye_ya_mur.h"

#include <BlynkSimpleShieldEsp8266.h>

char auth[] = "8jjOqik7ZfCe8NYHPFWJaLK9di0VoemG";

char ssid[] = "mucitpark";

char pass[] = "mucitpark388";




#define EspSerial Serial

#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

void setup()

{

genel_setup();
sss_setup();
Serial.begin(115200);

pinMode(13,OUTPUT);

EspSerial.begin(ESP8266_BAUD);

delay(10);

Blynk.begin(auth, wifi, ssid, pass);



}

void loop()

{

   genel_loop();
   sss_loop();

Blynk.run();
Blynk.virtualWrite(V0, 0.2);
Blynk.virtualWrite(V1, 80);
Blynk.virtualWrite(V2, random(15,17));
Blynk.virtualWrite(V3, random(35,40));
Blynk.virtualWrite(V4, random(26,28));
Blynk.virtualWrite(V5, random(80,90));

}
