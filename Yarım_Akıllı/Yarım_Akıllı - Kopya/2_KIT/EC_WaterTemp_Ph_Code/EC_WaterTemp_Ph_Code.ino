#include "Ec_WaterTemp.h"
#include "PH_sensor.h"



void setup()
{
  Ec_WaterTemp_Setup();
  Ph_Setup();
  Water_Temp_Setup();
}

void loop()
{
  Ec_WaterTemp_Loop();
  Ph_Loop();
  Water_Temp_Loop();
  
}
