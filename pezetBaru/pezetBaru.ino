#include <PZEM004T.h>
#include <SoftwareSerial.h> // Arduino IDE <1.6.6
PZEM004T pzem(2,3);  // (RX,TX) connect to TX,RX of PZEM
IPAddress ip(192,168,1,1);
void setup() {
  Serial.begin(9600);
  pzem.setAddress(ip);
}
void loop() {
  float v = pzem.voltage(ip);
  if (v < 0.0) v = 0.0;
  Serial.print(v);Serial.print("V; ");
  Serial.println(" ");
  float i = pzem.current(ip);
  if (i < 0.0) i = 0.0;
  Serial.print(i);Serial.print("A; ");
  Serial.println(" ");
  float p = pzem.power(ip);
  if (p < 0.0) p = 0.0;
  Serial.print(p);Serial.print("W; ");
  Serial.println(" ");
  float e = pzem.energy(ip);
  Serial.print("PF= ");Serial.print((p)/(v*i));
  Serial.println(" ");
  Serial.println();
  delay(250);
}
