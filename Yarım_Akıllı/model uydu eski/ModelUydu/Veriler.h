void AlinanVerileriEkranaYazdir(ModelUyduVeriler veriler )
{
  //Serial.println(veriler.speed);
}

void GonderilecekVerileriDuzenle(ModelUyduVeriler *veriler)
{
  veriler ->sayac =sayac/1000;
  veriler ->flat =flat;
  veriler->flon = flon;
  veriler->alti = alt;
  veriler->year = year;
  veriler->month = month;
  veriler->day = day;
  veriler->hour = hour;
  veriler->minute = minute;
  veriler->second = second;
  veriler->x = (int)mpu6050.getAngleX();
  veriler->y = (int)mpu6050.getAngleY();
  veriler->z = (int)mpu6050.getAngleZ();
  veriler->temp = (int)bme.readTemperature();
  veriler->press = (int)(bme.readPressure() / 100.0F);
  veriler->bmeAlti = (int)bme.readAltitude(SEALEVELPRESSURE_HPA) - x;
  veriler->speed = (int)HizHesapla();
  veriler->voltage = (int)busvoltage;
}
