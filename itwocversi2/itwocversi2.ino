//#include <EmonLib.h>
//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//EnergyMonitor emon1;
#define RELAY_CH1  31
#define RELAY_CH2  32
#define RELAY_CH3  33
#define RELAY_CH4  34
#define RELAY_CH5  35
#define RELAY_CH6  36
#define RELAY_CH7  37
#define RELAY_CH8  38
double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;
LiquidCrystal_I2C lcd(0x20,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Power");
  //lcd.setCursor(2,1);
  //lcd.print("Love");
   //lcd.setCursor(0,2);
  //lcd.print("you");
   //lcd.setCursor(2,3);
  //lcd.print("From the bottom of my soul");
  //  emon1.voltage(0, 700.9, 1.7);  // Voltage: input pin, calibration, phase_shift
  //emon1.current(A1, 105.1); 
        //pinMode(RELAY_CH1, OUTPUT); 
   //digitalWrite(RELAY_CH1, HIGH);
}


void loop()
{
    lcd.init();
  sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-210.2)+210.2;
  Serial.println(Veff);
  lcd.clear() 
  lcd.println(Veff);
  VmaxD=0;
}
         pinMode(RELAY_CH1, OUTPUT); 
   digitalWrite(RELAY_CH1, LOW);
   delay(1000);
      pinMode(RELAY_CH1, OUTPUT); 
   digitalWrite(RELAY_CH1, HIGH);
   delay(1000);
//emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
 
//  float realPower       = emon1.realPower;        //extract Real Power into variable
  //float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  //float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  //float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  //float Irms            = emon1.Irms;

 
 // lcd.print(supplyVoltage);   
  
}
