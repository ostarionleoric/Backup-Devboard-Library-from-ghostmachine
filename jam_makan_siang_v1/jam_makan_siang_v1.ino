// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance
int pin = 2;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6); // Multiplication factor to convert nano seconds into seconds
float sinpi;
float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
int ctr;

float P;
float Q;
float S;
float faktorr;

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(A1, 100, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A0, 15.25);       // Current: input pin, calibration.
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;   
  
  Serial.println(" ");//extract Irms into Variable
  Serial.print("tegangang  =");
  Serial.println(supplyVoltage);
  Serial.print("arus  =");
  Serial.println(Irms);
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
   //Serial.print(angle_max, 2); // Print the result
   //Serial.print(",");
   //Serial.println(pf_max, 2);
 // lcd.clear();
   //lcd.setCursor(0,0);
  sinpi = sin(angle_max / rads); 
   P=(supplyVoltage*Irms)*pf_max;
   
   S=supplyVoltage*Irms;
Q=S+((supplyVoltage*Irms)*sinpi);
   
   Serial.print("PF=");
//   lcd.setCursor(4,0);
      Serial.print(pf_max);
      Serial.println(" ");
      Serial.print("S=");
   Serial.print(supplyVoltage*Irms);
   Serial.println(" watt ");
   Serial.print("Q=");
   //Serial.println(Q);
   Serial.println((supplyVoltage*Irms)*sinpi);
   sinpi = sin((abs(angle_max)) / rads);
   Serial.print("P=");
   Serial.print((supplyVoltage*Irms)*(abs(pf_max)));
   Serial.print(" atau ");
   Serial.println(realPower);
   
   Serial.print("beda fasanya=");
   
   Serial.print(angle_max);
   Serial.println(" ");
    //Serial.print("sinpi nya=");
   
   //Serial.print(sinpi);
  // Serial.println(" ");
   
      Serial.print("Nilai Kospinya=");
     faktorr = (abs(powerFActor)+0.10);
   //Serial.print(((vrms*Irms)*pf_max)/((vrms*Irms)*sinpi));
   Serial.print(P/S);
   Serial.print(" atau ");
   Serial.print(powerFActor);
   Serial.print(" atau ");
   Serial.print(faktorr);
   Serial.println(" ");

   if( abs(pf_max) <= 0.96){
    digitalWrite(4, HIGH);
   }
   if( abs(pf_max) <= 0.96){
     
    digitalWrite(5, HIGH);
   }
   if( abs(pf_max) <= 0.96) {
  
    digitalWrite(6, HIGH);
   }
   if( abs(pf_max) <= 0.96) {
 
    digitalWrite(7, HIGH);
   }
   if( abs(pf_max) <= 0.96) {
 
    digitalWrite(8, HIGH);
   }
   
   else {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
   }
   //delay(500);
   angle = 0; // Reset variables for next test
   angle_max = 0;
  
}
