/* Original code by olehs, visit https://github.com/olehs/PZEM004T/
Modified by nanda
*/
#include <PZEM004T.h>
#include <SoftwareSerial.h> 
PZEM004T pzem(2,3);  // (RX,TX) 
IPAddress ip(192,168,1,1);
void setup() {Serial.begin(9600);pzem.setAddress(ip);}
void loop() {float v = pzem.voltage(ip);
if (v < 0.0) v = 0.0;
Serial.print("That Damn Voltage ");
Serial.print(v);Serial.print("V; ");
Serial.println(" ");
float i = pzem.current(ip);
if (i < 0.0) i = 0.0;
Serial.print("F*cking Current ");
Serial.print(i);Serial.print(" A; ");
Serial.println(" ");
float p = pzem.power(ip);
if (p < 0.0) p = 0.0;
Serial.print("THE POWER ");
Serial.print(p);Serial.print(" Watt; ");
Serial.println(" ");
float e = pzem.energy(ip);
Serial.print("A F*CK*NG PowerFactor= ");
Serial.print(((p)/(v*i))-0.08);//0.08 
Serial.println(" ");
Serial.println();
delay(100);
}
