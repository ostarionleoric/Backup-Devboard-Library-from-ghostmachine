//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("SILAHKAN");
  lcd.setCursor(8,1);
  lcd.print("AMBIL");
   lcd.setCursor(8,2);
  lcd.print("KOIN");
   lcd.setCursor(1,3);
  lcd.print("TEURIMONG GEUNASEH");
}


void loop()
{
}
