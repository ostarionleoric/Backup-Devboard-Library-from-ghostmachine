//Michael Klements
//The DIY Life
//27 October 2014
//update 08/06/2018

#include <LiquidCrystal.h>

int voltagePin = 1;              //Assign CT input
int currentPin = 2;              //Assign CT input

double kilos = 0;
int peakPower = 0;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //Assign LCD screen pins

void setup() 
{ 
  lcd.begin(16,2);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Yuwaldi Away...");
}

void loop() 
{ 
  int current = 0;
  int voltage = 0;
  int maxCurrent = 0;
  int minCurrent = 1000;

  // baca tegangan AC pin A1
  voltage = analogRead(voltagePin);    //Reads voltage input

  //baca 200x untuk tau arus maimum
  //Monitors and logs the current input for 200 cycles to determine max and min current
   for (int i=0 ; i<=200 ; i++)  {
    current = analogRead(currentPin);    //Reads current input pin A1 0 - 1023

    // jika arus baca lebih besar sama dengan arus max
    if(current >= maxCurrent)
      maxCurrent = current; // maka arus max = arus baca
    else if(current <= minCurrent) // jika tidak, itu arus minimum
      minCurrent = current;
  }

  // jika arus maksimum lebih kecil 517
  if (maxCurrent <= 517)
  {
    maxCurrent = 516; // maka arus maksumum 516
  }

  // hitung 
  //Calculates RMS current based on maximum value
  // 
  double RMSCurrent = ((maxCurrent - 516)*0.707)/11.8337;    //Calculates RMS current based on maximum value

  // hitung RMS daya ... tegangan x arus efektif
  int RMSPower = voltage*RMSCurrent;    //Calculates RMS Power Assuming Voltage 220VAC, change to 110VAC accordingly

  // apakah rms lebih besar rms
  if (RMSPower > peakPower)
  {
    peakPower = RMSPower;
  }

  // total daya efeftif 
  kilos = kilos + (RMSPower * (2.05/60/60/1000));    //Calculate kilowatt hours used

  // 2 detik untuk hitung jumlah 
  delay (2000);
  lcd.clear();

  // tampilkan tegangan
  lcd.setCursor(0,0);           // Displays all current data
  lcd.print(voltage);
  lcd.print("V");

  // tampilkan
  lcd.setCursor(8,0);
  lcd.print(RMSCurrent);
  lcd.print("A");
  // tampilkan daya efektif
  lcd.setCursor(0,1);
  lcd.print(RMSPower);
  lcd.print("W");
  // tampilkan kwh
  lcd.setCursor(8,1);
  lcd.print(kilos);
  lcd.print("kWh");
}
