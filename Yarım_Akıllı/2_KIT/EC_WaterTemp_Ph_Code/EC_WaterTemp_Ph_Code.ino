
long int x = 0;
long int y ;
void Ec_WaterTemp_Setup();
 void Ph_Setup();
 void Ec_WaterTemp_Loop();
 void Ph_Loop();
void Water_Temp_Loop();
void Water_Temp_Setup();

void setup()
{
 Ec_WaterTemp_Setup();
 Ph_Setup() ;
}

void loop()
{
  
 
   AnalagRead(); /////////////// İKİ TANE ANALOG OKUMA YAPIYORSUNN!!!!!!!!!!!!!!!!!!!!!

}


void AnalagRead()
{
  y = millis();
  if (y - x <= 10000) 
  {
    
    Ec_WaterTemp_Loop();
    Water_Temp_Loop();

  }
  else if (y - x > 10000 && y - x <= 20000)
  {
    
   Ph_Loop();
   Water_Temp_Setup();

  }

  else {
    
    x = millis();
  }

}
