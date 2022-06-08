// Code for Arduino Tachometer using IR Sensor

//#include <LiquidCrystal.h>
//LiquidCrystal lcd(3, 2, 4, 5, 6, 7);

#define sensor 2
//#define start 10

int delay1()
{
  //unsigned int long k;
    int i,j;
    unsigned int count=0;
    for(i=0;i<1000;i++) 
    {
      for(j=0;j<1227;j++)
      {
       if(digitalRead(sensor))
       {
         count++;
         while(digitalRead(sensor));
       }
    }
  }
    return count;
}

void setup() 
{
  pinMode(sensor, INPUT);
 // pinMode(start, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  delay(2000);
  digitalWrite(sensor, HIGH);
}

void loop() 
{
  
     unsigned int time=0,RPM=0;
     time=delay1();
     RPM=(time*12)/3;
     delay(2000);
  
     Serial.println(RPM);
     //delay(5000);
}
