#include<Arduino.h>

#define RPWM 5
#define LPWM 6
#define REN 8
#define LEN 9


#define RPWM3 17
#define LPWM3 16
#define REN3 15
#define LEN3 14


#define RPWM1 13
#define LPWM1 12
#define REN1 11
#define LEN1 10

#define ENA 2
#define EN1 3
#define EN2 4

void forward();
void back();
void turnRight();
void turnLeft();
void stopMotors();





char t;



void setup()
{
  Serial.begin(9600);

  pinMode(RPWM,OUTPUT);
  pinMode(LPWM,OUTPUT);
  pinMode(LEN,OUTPUT);
  pinMode(REN,OUTPUT);
  digitalWrite(REN,HIGH);
  digitalWrite(LEN,HIGH);

  pinMode(RPWM3,OUTPUT);
  pinMode(LPWM3,OUTPUT);
  pinMode(LEN3,OUTPUT);
  pinMode(REN3,OUTPUT);
  digitalWrite(REN3,HIGH);
  digitalWrite(LEN3,HIGH);

  pinMode(RPWM1,OUTPUT);
  pinMode(LPWM1,OUTPUT);
  pinMode(LEN1,OUTPUT);
  pinMode(REN1,OUTPUT);
  digitalWrite(REN1,HIGH);
  digitalWrite(LEN1,HIGH);


  pinMode(ENA,OUTPUT);
  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);


}

void loop() 
{
  
  if(Serial.available()>0)
  {
  t = Serial.read();
  Serial.println(t);
  
  }

  if(t == 'F')
  {            
    forward();
  Serial.println("motor ileri");

  }

  else if(t == 'B')
  {      
    back();
   Serial.println("motor geri");
  }
  
   else if(t == 'L')
  {      
    turnLeft();
   Serial.println("motor sola");
  }

   else if(t == 'R')
  {      
    turnRight();
   Serial.println("motor sağa");
  }

  else if (t == 'S')
  {
    stopMotors();
    Serial.println("motor dur");
  }
   
}


void turnRight()
{
    analogWrite(RPWM,0);
    analogWrite(LPWM,255);
    analogWrite(RPWM1,0);
    analogWrite(LPWM1,255);
    analogWrite(ENA,255);
    analogWrite(RPWM3,255);
    analogWrite(LPWM3,0);
    digitalWrite(EN1,LOW);
    digitalWrite(EN2,HIGH);
}

void turnLeft()
{
    analogWrite(RPWM,255);
    analogWrite(LPWM,0);
    analogWrite(RPWM1,255);
    analogWrite(LPWM1,0);
    analogWrite(ENA,255);
    analogWrite(RPWM3,0);
    analogWrite(LPWM3,255);
    digitalWrite(EN1,HIGH);
    digitalWrite(EN2,LOW);
}

void forward()
{
    analogWrite(RPWM,0);
    analogWrite(LPWM,255);
    analogWrite(RPWM1,0);
    analogWrite(LPWM1,255);
    analogWrite(RPWM3,0);
    analogWrite(LPWM3,255);
    analogWrite(ENA,255);
    digitalWrite(EN1,HIGH);
    digitalWrite(EN2,LOW);

}

void back()
{
    analogWrite(RPWM,255);
    analogWrite(LPWM,0);
    analogWrite(RPWM1,255);
    analogWrite(LPWM1,0);
    analogWrite(RPWM3,255);
    analogWrite(LPWM3,0);
    analogWrite(ENA,255);
    digitalWrite(EN1,LOW);
    digitalWrite(EN2,HIGH);
}

void stopMotors ()
{
    analogWrite(RPWM,0);
    analogWrite(LPWM,0);
    analogWrite(RPWM1,0);
    analogWrite(LPWM1,0);
     analogWrite(RPWM3,0);
    analogWrite(LPWM3,0);
    analogWrite(ENA,0);
    digitalWrite(EN1,0);
    digitalWrite(EN2,0);
}
