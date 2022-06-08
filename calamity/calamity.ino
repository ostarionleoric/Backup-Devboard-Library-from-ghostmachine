// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  
  //emon1.voltage(A0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  //emon1.current(A1, 111.1);       // Current: input pin, calibration.
  emon1.voltage(A1, 730.9, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A0, 105.1);       // Current: input pin, calibration.
}

void loop()
{
  int bacaAnal= analogRead(A0);

  
  emon1.calcIrms(200);
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
 
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  //Serial.println(bacaAnal);

  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
if(supplyVoltage <40){
Serial.println("0");  
}
else{
Serial.println(supplyVoltage,0);
  }

 Serial.println(bacaAnal);  
}
