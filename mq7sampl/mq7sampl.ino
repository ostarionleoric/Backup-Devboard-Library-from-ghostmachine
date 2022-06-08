#include "MQ7.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

MQ7 mq7(A0, 5.0);

void setup()
{
  Serial.begin(9600);
    lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
}

void loop()
{
  Serial.print("Karbon Monoksida : ");
  Serial.println(mq7.getPPM());
    lcd.setCursor(3,0);
  lcd.print("Karbon Monoksida : ");
    lcd.setCursor(2,1);
  lcd.print(mq7.getPPM());
  delay(500);
 lcd.clear();
}
