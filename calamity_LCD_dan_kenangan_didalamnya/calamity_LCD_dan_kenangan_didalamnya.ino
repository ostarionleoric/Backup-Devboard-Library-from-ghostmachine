// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

void setup()
{  
  Serial.begin(9600);
  lcd.init();             
  lcd.backlight();
  //emon1.voltage(A0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  //emon1.current(A1, 111.1);       // Current: input pin, calibration.
  emon1.voltage(A0, 700.9, 1.5);  // Voltage: input pin, calibration, phase_shift
  emon1.current(A1, 111.1);       // Current: input pin, calibration.
}

void loop()
{
  int bacaAnal= analogRead(A0);

  
  emon1.calcIrms(200);
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
 float powerFActor     = emon1.powerFactor;
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  //Serial.println(bacaAnal);

  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
//  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  float s = supplyVoltage*Irms;
if(supplyVoltage <40){
  lcd.clear();
Serial.println("0");  
lcd.setCursor(0,0);
 lcd.print("V = 0");
lcd.setCursor(4,0);
  //lcd.print(supplyVoltage,0);
  lcd.print("0");
lcd.setCursor(12,0);
  lcd.print("I = 0");
lcd.setCursor(15,0);
  lcd.print(Irms,2);
   lcd.setCursor(0,1);
 lcd.print("S =");
lcd.setCursor(4,1);
  lcd.print(supplyVoltage*Irms,1);
  
  lcd.setCursor(12,1);
  lcd.print("PF =");
lcd.setCursor(15,1);
lcd.print(abs(powerFActor));
 // lcd.print(pf_max,2);

   lcd.setCursor(0,2);
 lcd.print("P =");
lcd.setCursor(4,2);
lcd.print(abs(realPower));
  //lcd.print((supplyVoltage*Irms)*(abs(pf_max)),1);
   lcd.setCursor(0,3);
 lcd.print("Q =");
lcd.setCursor(4,3);
lcd.print(sqrt((s*s)-(realPower*realPower)));
 // lcd.print((supplyVoltage*Irms)*sinpi,1);
   
   delay(20);
}
else{
  lcd.clear();
Serial.println(supplyVoltage,0);
lcd.setCursor(0,0);
 lcd.print("V =");
lcd.setCursor(4,0);
  lcd.print(supplyVoltage,0);
lcd.setCursor(12,0);
  lcd.print("I =");
lcd.setCursor(15,0);
  lcd.print(Irms,2);
   lcd.setCursor(0,1);
 lcd.print("S =");
lcd.setCursor(4,1);
  lcd.print(supplyVoltage*Irms,1);
  lcd.setCursor(12,1);
  lcd.print("PF =");
lcd.setCursor(15,1);
  //lcd.print(pf_max,2);
  lcd.print(abs(powerFActor));

   lcd.setCursor(0,2);
 lcd.print("P =");
lcd.setCursor(4,2);
lcd.print(abs(realPower));
 // lcd.print((supplyVoltage*Irms)*(abs(pf_max)),1);realPower
 
   lcd.setCursor(0,3);
 lcd.print("Q =");
lcd.setCursor(4,3);
lcd.print(sqrt((s*s)-(realPower*realPower)));
  //lcd.print((supplyVoltage*Irms)*sinpi,1);
   
   delay(20);
  }

// Serial.println(bacaAnal);  
}
