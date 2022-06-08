#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  
int sensorPin = 7; 
int ledPin = 13;    
int sensorValue = 0;
int setpoint;
const int buttonPin = 5;    

int mode;

float value = 0;
float rev = 0;
int rpm;
int oldtime = 0;
int rpmsetpoint;
int time;

int buttonState = 0;         // variable for reading the pushbutton status


void isr() {
  rev++;
}


void setup() {
pinMode(buttonPin, INPUT);
  lcd.init();
  lcd.init();
   pinMode(8,OUTPUT);
  lcd.backlight();
      attachInterrupt(digitalPinToInterrupt (2), isr, RISING);
      mode = 0;
}

void loop() {
     detachInterrupt(digitalPinToInterrupt(2));      
  time = millis() - oldtime;    
  rpm = (rev / time) * 15000;   
  oldtime = millis();          
  rev = 0;
 
  buttonState = digitalRead(buttonPin);

attachInterrupt(digitalPinToInterrupt (2), isr, RISING);
Serial.println(rpm);
 
  lcd.clear();
  sensorValue = analogRead(sensorPin);
  setpoint= map(sensorValue, 0, 1023, 0, 101);
  Serial.println(sensorValue);
  lcd.setCursor(3,0);
 // lcd.print("RPM : ");
 // lcd.print(rpm);
rpmsetpoint=rpm/3.8;  
  lcd.setCursor(1,1);
  lcd.print("RPM :");
  lcd.print(rpmsetpoint);
  //lcd.print("%");
  delay(50);




  //lcd.setCursor(1,2);
 // lcd.print("MODE :");
  //lcd.print(buttonState);
  //lcd.print("");
  delay(500);

if(buttonState == 1 && mode == 0 )
{
 
  lcd.setCursor(1,2);
  lcd.print("MODE :");
  lcd.print("SATU");
  delay(500);
   mode = 1;
  //lcd.print("");
}
else if(buttonState == 1 && mode == 1)
{
  
  lcd.setCursor(1,2);
  lcd.print("MODE :");
  lcd.print("DUA");
  delay(500);
  //lcd.print("");
  mode = 0;
}

else if(rpm<100 &&  rpm<577){
   digitalWrite(8, HIGH);
}
else{
   digitalWrite(8, LOW);
}
}
