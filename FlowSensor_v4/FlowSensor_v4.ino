#include <Wire.h>

byte indikator = 13;
byte sensorInt = 0; 
byte flowsensor = 2;
float konstanta = 4.5;
volatile byte pulseCount;
float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long oldTime;

void setup()
{
Serial.begin(9600);
pinMode(indikator, OUTPUT);
//digitalWrite(indikator, HIGH); 
pinMode(flowsensor, INPUT);
digitalWrite(flowsensor, HIGH);
pulseCount = 0;
debit = 0.0;
flowmlt = 0;
totalmlt = 0;
oldTime = 0;
attachInterrupt(sensorInt, pulseCounter, RISING);
}

void loop()
{
if((millis() - oldTime) > 100) 
{ 
detachInterrupt(sensorInt);
debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
oldTime = millis();
flowmlt = (debit / 60) * 1000;
totalmlt = flowmlt;
//unsigned int frac;
Serial.println("HASIL PENGUKURAN");

//Serial.print("Debit Air : ");
//Serial.print(int(debit));
//Serial.println(" L/min");

Serial.print("Volume    : "); 
Serial.print(totalmlt);
Serial.print(" mL"); 

//pulseCount = 0;
attachInterrupt(sensorInt, pulseCounter, RISING);
}

}

void pulseCounter()
{
  if(totalmlt>=100){
  pulseCount++;
  digitalWrite(indikator, HIGH); 
  
}
else{
  pulseCount++;
  digitalWrite(indikator, LOW); 

}

//pulseCount =0;
}
