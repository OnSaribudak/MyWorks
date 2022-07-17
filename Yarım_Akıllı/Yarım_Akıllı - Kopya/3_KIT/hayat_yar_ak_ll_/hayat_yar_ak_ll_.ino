#include"Communication.h"


const int relay = 16;
const int relay2 = 14;



void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
 
  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  Serial.println("Current Flowing");
  delay(10000); 
  

  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
  Serial.println("Current not Flowing");
  delay(10000);
}
