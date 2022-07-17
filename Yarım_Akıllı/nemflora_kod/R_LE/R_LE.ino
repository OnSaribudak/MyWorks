
const int relay = 14;
int analogdan_gelen_deger; 
void setup() {
  Serial.begin(115200);
  pinMode(relay,OUTPUT);
 
}

void loop() {

analogdan_gelen_deger = ((1024-analogRead(A0))/10); 
Serial.println(analogdan_gelen_deger);

if (analogdan_gelen_deger < 40){
  digitalWrite(relay,LOW);
}

 else {
  digitalWrite(relay,HIGH);

  
 }


} 
