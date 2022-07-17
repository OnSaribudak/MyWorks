
int suSeviyesi = A0;      
int yagmurPin = A1; 
int esikDegeri = 250;       
int esikDegeri2 = 180;        
int sensor = 8;                 
int veri;  
int suLevel  ;                      

void sss_setup() {
  pinMode(sensor,INPUT);
  Serial.begin(9600);
}
void sss_loop() {
  bool okunan = digitalRead(sensor);
  suLevel = analogRead(suSeviyesi);
  Serial.println(veri);    
  if(veri > esikDegeri){           
    Serial.println("Su seviyesi yeterli seviyede");
    delay(500);
  }
  else{                            
    Serial.println("Su seviyesi yetersiz");
    delay(500);
  }

  
  
    veri = analogRead(yagmurPin);  
    Serial.println(veri);   
  if(veri > esikDegeri2){  
       
    Serial.println("Yagmur yagıyor");
    delay(500);
  }
  else{                            
    Serial.println("Yagmur yagmıyor.");
    delay(500);
  }
  return suLevel ;
}
