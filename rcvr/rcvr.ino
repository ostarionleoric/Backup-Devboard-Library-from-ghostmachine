#include <SoftwareSerial.h>
#define tx 2
#define rx 3
SoftwareSerial bt(rx, tx); //RX, TX
char g=0;
int ENB10 = 10;
int ENB11 = 11;

int ENA5 = 5;
int ENA6 = 6;
int lm1=8; //left motor output 1
int lm2=12; //left motor output 2
int rm1=7;  //right motor output 1
int rm2=4;  //right motor output 2


void setup()
{
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(tx, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(rx, INPUT);
    pinMode(lm1,OUTPUT);
  pinMode(lm2,OUTPUT);
  pinMode(rm1,OUTPUT);
  pinMode(rm2,OUTPUT);
    analogWrite(ENB10, 255);
analogWrite(ENB11, 255);
analogWrite(ENA5, 255);
analogWrite(ENA6, 255);
}
void loop()
{
  if(bt.available()>0)
  {
    g = bt.read();
    Serial.println(bt.read());
    if(g>60){
      digitalWrite(13,HIGH);
      ForWard();
    }
    else{
      digitalWrite(13,LOW);
      sTOP();
    }
  }
}
  void ForWard()
  {
   digitalWrite(lm1,HIGH);
   digitalWrite(lm2,LOW);
   digitalWrite(rm1,HIGH);
   digitalWrite(rm2,LOW);
  } 
  void BackWard()
  {
   digitalWrite(lm1,LOW);
   digitalWrite(lm2,HIGH);
   digitalWrite(rm1,LOW);
   digitalWrite(rm2,HIGH);
  }
  void Left()
  {
   digitalWrite(lm1,LOW);
   digitalWrite(lm2,HIGH);
   digitalWrite(rm1,HIGH);
   digitalWrite(rm2,LOW);
  } 
  void Right()
  {
   digitalWrite(lm1,HIGH);
   digitalWrite(lm2,LOW);
   digitalWrite(rm1,LOW);
   digitalWrite(rm2,HIGH);
  }  

    void sTOP()
  {
   digitalWrite(lm1,LOW);
   digitalWrite(lm2,LOW);
   digitalWrite(rm1,LOW);
   digitalWrite(rm2,LOW);
  }
