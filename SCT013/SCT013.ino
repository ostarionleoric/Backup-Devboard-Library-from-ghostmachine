#include "EmonLib.h"
// Include Emon Library
EnergyMonitor emon1;
// Create an instance
void setup()
{
  Serial.begin(9600);

  emon1.current(A0, 119.1);             // Current: input pin, calibration.
}

void loop()
{
double Irms = emon1.calcIrms(1480);  // Calculate Irms only
Serial.print(Irms*220.0);           // Apparent power
  Serial.print(" i rms = ");
  Serial.println(Irms);             // Irms
}
