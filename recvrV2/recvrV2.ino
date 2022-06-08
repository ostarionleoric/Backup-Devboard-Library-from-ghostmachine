#include <SoftwareSerial.h>
#define tx 2
#define rx 3
SoftwareSerial bt(rx, tx); //RX, TX
void setup()
{
  Serial.begin(115200);
  bt.begin(38400);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
}
void loop()
{
  if(bt.available()>0)
  {
    Serial.println(bt.read());
  }
}
