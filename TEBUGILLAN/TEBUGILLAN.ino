#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int sensorPin = A0; 
int ledPin = 13;    
int sensorValue = 0;
int setpoint;
const int buttonPin = 2;     // the number of the pushbutton pin
//const int ledPin =  13;      // the number of the LED pin
float value = 0;
float rev = 0;
int rpm;
int oldtime = 0;
int rpmsetpoint;
int time;
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void isr() {
  rev++;
}


void setup() {

  lcd.init();
  lcd.init();
   pinMode(8,OUTPUT);
  lcd.backlight();
      attachInterrupt(digitalPinToInterrupt (2), isr, RISING);
}

void loop() {
     detachInterrupt(digitalPinToInterrupt(2));      
  time = millis() - oldtime;    
  rpm = (rev / time) * 15000;   
  oldtime = millis();          
  rev = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

attachInterrupt(digitalPinToInterrupt (2), isr, RISING);
Serial.println(rpm);
  lcd.clear();
  sensorValue = analogRead(sensorPin);
  setpoint= map(sensorValue, 0, 1023, 0, 101);
  Serial.println(sensorValue);
  lcd.setCursor(3,0);
  lcd.print("RPM : ");
  lcd.print(rpm);
  
  lcd.setCursor(1,1);
  lcd.print("Setpoint :");
  lcd.print(setpoint);
  lcd.print("%");
  delay(50);


rpmsetpoint=(rpm-(rpm*(setpoint/100)));

  lcd.setCursor(1,2);
  lcd.print("rpm :");
  lcd.print(rpmsetpoint);
  //lcd.print("");
  delay(500);
  
if(rpm>700 && rpm<1000){
   digitalWrite(8, LOW);
}
else{
   digitalWrite(8, HIGH);
}
}
