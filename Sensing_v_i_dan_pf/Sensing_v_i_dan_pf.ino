#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance
int pin = 2;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float derajatsudut = 360;
float frekwensi = 50;
float nanodetik = 1 * pow (10,-6); // Multiplication factor to convert nanodetik seconds into seconds
float sinpi;
float pf;
float sudutfasa;
float pf_max = 0;
float sudutfasa_max = 0;
int ctr;

float P;
float Q;
float S;
float faktorr;

void setup()
{  
  Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
  //lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  emon1.voltage(A1, 98, 1.7);  // Voltage: input pin, calibration, phase_shift
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
  // 1st line calculates the phase sudutfasa in derajatsuduts from differentiated time pulse
  // Function COS uses radians not derajatsudut's hence conversion made by dividing sudutfasa / 57.2958
   sudutfasa = ((((pulseIn(pin, HIGH)) * nanodetik)* derajatsudut)* frekwensi);
  // pf = cos(sudutfasa / rads); 
   
   if (sudutfasa > sudutfasa_max) // Test if the sudutfasa is maximum sudutfasa
     {
      sudutfasa_max = sudutfasa; // If maximum record in variable "sudutfasa_max"
      pf_max = cos(sudutfasa_max / rads); // Calc PF from "sudutfasa_max"
     }
   }
   if (sudutfasa_max > 360) // If the calculation is higher than 360 do following...
   {
    sudutfasa_max = 0; // assign the 0 to "sudutfasa_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   if (sudutfasa_max == 0) // If the calculation is higher than 360 do following...
   {
    sudutfasa_max = 0; // assign the 0 to "sudutfasa_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   //Serial.print(sudutfasa_max, 2); // Print the result
   //Serial.print(",");
   //Serial.println(pf_max, 2);
 // lcd.clear();
   //lcd.setCursor(0,0);
  //sinpi = sin(sudutfasa_max / rads); 
   P=(supplyVoltage*Irms)*pf_max;
   sinpi = sin((abs(sudutfasa_max)) / rads);
   S=supplyVoltage*Irms;
//Q=S+((supplyVoltage*Irms)*sinpi);
Q=((supplyVoltage*Irms)*sinpi);
   lcd.setCursor(0,0);
 lcd.print("V =");
lcd.setCursor(4,0);
  lcd.print(supplyVoltage,0);
lcd.setCursor(12,0);
  lcd.print("I =");
lcd.setCursor(15,0);
  lcd.print(Irms,1);
   lcd.setCursor(0,1);
 lcd.print("S =");
lcd.setCursor(4,1);
  lcd.print(supplyVoltage*Irms,1);
  lcd.setCursor(12,1);
  lcd.print("PF =");
lcd.setCursor(15,1);
  lcd.print(pf_max,2);

   lcd.setCursor(0,2);
 lcd.print("P =");
lcd.setCursor(4,2);
  lcd.print((supplyVoltage*Irms)*(abs(pf_max)),1);
   lcd.setCursor(0,3);
 lcd.print("Q =");
lcd.setCursor(4,3);
  lcd.print((supplyVoltage*Irms)*sinpi,1);
    
 // lcd.setCursor(0,1);
 // lcd.println(pf_max, 2);
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
   
   Serial.print("P=");
   Serial.print((supplyVoltage*Irms)*(abs(pf_max)));
   Serial.print(" atau ");
   Serial.println(realPower);
   
   Serial.print("beda fasanya=");
   
   Serial.print(sudutfasa_max);
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
       

  //lcd.clear() ;
   sudutfasa = 0; // Reset variables for next test
   sudutfasa_max = 0;
  
}
