#include <Wire.h>
float Volt1;
float Volt;

void setup()
{
  Serial.begin(9600);
  Serial.println("Voltage: ");
 }
void loop()
{
      Volt1=analogRead(A0);
      Volt=((Volt1*0.00489)*5);
      Serial.print(Volt);
      Serial.println("V");
     
   delay(1000);
}
