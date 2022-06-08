// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

//zc
int pin = 13;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6);
float nilaixor;
float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
int ctr;

void setup()
{  
  pinMode(pin, INPUT);
  Serial.begin(9600);
  
  emon1.voltage(A0, 200.3, 1.3);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A1, 60);       // Current: input pin, calibration.
}

void loop()
{
   nilaixor=digitalRead(13);
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  float S = supplyVoltage * Irms;
  
  
  //float nilaiQ          = sqrt((apparentPower*apparentPower)-(realPower*realPower));
  //float nilaiP          = sqrt((S*S)-(realPower*realPower));
float nilaiQ          = sqrt((S*S)-(realPower*realPower));

for (ctr = 0; ctr <= 4; ctr++) // Perform 4 measurements then reset
  {
  // 1st line calculates the phase angle in degrees from differentiated time pulse
  // Function COS uses radians not Degree's hence conversion made by dividing angle / 57.2958
   angle = ((((pulseIn(pin, HIGH)) * nano)* degree)* frequency);
  // pf = cos(angle / rads); 
   
   if (angle > angle_max) // Test if the angle is maximum angle
     {
      angle_max = angle; // If maximum record in variable "angle_max"
      pf_max = cos(angle_max / rads); // Calc PF from "angle_max"
     }
   }
   if (angle_max > 360) // If the calculation is higher than 360 do following...
   {
    angle_max = 0; // assign the 0 to "angle_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   if (angle_max == 0) // If the calculation is higher than 360 do following...
   {
    angle_max = 0; // assign the 0 to "angle_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   float P = S * pf_max;
   Serial.print("P = ");
   Serial.print(P);
   Serial.println("  ");
   Serial.print("S = ");
   Serial.print(S);
   Serial.println("  ");

   
   //Serial.print("Ph-Shift=");
   
   //Serial.print(angle);
   //Serial.print(" & ");
  Serial.print("Q = ");
  Serial.print(nilaiQ,0);
  Serial.print(" & ");
  Serial.print(supplyVoltage,2);
  Serial.print(" & ");
  Serial.print(Irms);
  Serial.print(" & PF =");
  Serial.print(powerFactor);
   Serial.print(" atau =");
   Serial.print(pf_max, 2);
      Serial.print(" atau =");
   Serial.println(P/S, 2);
  //Serial.println(emon1.voltage,0);
}
