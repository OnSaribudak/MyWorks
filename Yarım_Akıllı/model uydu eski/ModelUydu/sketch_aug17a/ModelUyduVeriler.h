typedef struct ModelUyduVeriler {
  // GPS 
  float flat;
  float flon;
  int alti;
  int year;
  byte month;
  byte day;
  byte hour;
  byte minute;
  byte second;
  // GPS

  // MPU
  int x;
  int y;
  int z;
  // MPU

  // BME
  int temp;
  int press;
  int bmeAlti;
  int speed;
  // BME

  //VOLT
  int voltage;  
  //VOLT
  
} ModelUyduVeriler;