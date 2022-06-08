int analogInPin = A1;
int analogInPin1 = A0;
int sensorValue = 0;
int sensorValue1 = 0;
int outputValue = 0;
int outputValue1 = 0;
int transistorPin = 3;
int transistorPin2 = 4;
const int  buttonPin = 40;
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int kambing = 0;
const int s0_pin = 8;  
const int s1_pin = 9;  
const int s2_pin = 12;  
const int s3_pin = 11;  
const int out_pin = 10;   
const int tombol10000 = 24;
const int tombol5000 = 22;


int tombol100001;
int tombol50001;
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup()

{

Serial.begin(9600);
pinMode(tombol10000, INPUT);
pinMode(tombol5000, INPUT);

pinMode(analogInPin, INPUT);
pinMode(analogInPin1, INPUT);
pinMode(transistorPin, OUTPUT);
pinMode(transistorPin2, OUTPUT);
pinMode(28, OUTPUT);
pinMode(30, OUTPUT);

pinMode(s0_pin, OUTPUT);
pinMode(s1_pin, OUTPUT);
pinMode(s2_pin, OUTPUT);
pinMode(s3_pin, OUTPUT);
pinMode(out_pin, INPUT);
digitalWrite(s0_pin,HIGH);
digitalWrite(s1_pin,LOW);

lcd.init();                      
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.50.000");
 
  
}

void loop()

{

tombol100001 = digitalRead(tombol10000);
tombol50001 = digitalRead(tombol5000);
buttonState = digitalRead(buttonPin);
sensorValue = analogRead(analogInPin);
sensorValue1 = analogRead(analogInPin);
outputValue = map(sensorValue, 0, 1023, 0, 255);
outputValue1 = map(sensorValue1, 0, 1023, 0, 255);


digitalWrite(s2_pin,LOW);
digitalWrite(s3_pin,LOW);
int red_color = pulseIn(out_pin, LOW);
red_color = map(red_color, 25,72,255,0);
delay(50);
digitalWrite(s2_pin,HIGH);
digitalWrite(s3_pin,HIGH);
int green_color = pulseIn(out_pin, LOW);
green_color = map(green_color, 30,90,255,0);
delay(50);
digitalWrite(s2_pin,LOW);

digitalWrite(s3_pin,HIGH);

int blue_color = pulseIn(out_pin, LOW);

blue_color = map(blue_color, 25,70,255,0);

delay(50);


Serial.print("RED: ");

Serial.print(red_color);

Serial.print("  ");

Serial.print("GREEN: ");

Serial.print(green_color);

Serial.print("  ");

Serial.print("BLUE: ");

Serial.print(blue_color);

Serial.println("  ");


  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      //Serial.println("on");
      Serial.print("numbers: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      //Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }

  lastButtonState = buttonState;


sensorValue = analogRead(analogInPin);
sensorValue1 = analogRead(analogInPin);
outputValue = map(sensorValue, 0, 1023, 0, 255);
outputValue1 = map(sensorValue1, 0, 1023, 0, 255);

  if (buttonPushCounter  == 6)  {
//    digitalWrite(ledPin, HIGH);
//kambing = 1;
digitalWrite(28, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, HIGH);
    analogWrite(transistorPin, 0);
analogWrite(transistorPin2, 0);
  } else {
analogWrite(transistorPin, outputValue);
analogWrite(transistorPin2, outputValue1);
digitalWrite(28, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, HIGH);
  //kambing = 0;
  //  digitalWrite(ledPin, LOW);
  }

if(red_color>-21 && red_color<28 && green_color>9 && green_color<80  && blue_color>38 && blue_color<108){  
//  a=1;
  Serial.println("uang 50000");
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  lcd.clear();
  lcd.print("Pilih Nominal");
  lcd.setCursor(0,1);
  lcd.print("Rp.10000/Rp.5000");
  
  
  //digitalWrite(6, HIGH);
  
}



else if(tombol100001 == HIGH ){
Serial.println("SILAHKAN PILIH PECAHAN YANG DI INGINKAN");    
  lcd.clear();
  lcd.print("Rp.10.000");
  lcd.setCursor(0,1);
  lcd.print("");
  analogWrite(transistorPin, outputValue);
digitalWrite(28, HIGH);  
  digitalWrite(30, HIGH);

           delay(1000);        
             }

else if(tombol50001 == HIGH ){
Serial.println("SILAHKAN PILIH PECAHAN YANG DI INGINKAN");    
  lcd.clear();
  lcd.print("Rp.5000");
  lcd.setCursor(0,1);
  lcd.print("");
analogWrite(transistorPin2, outputValue1);
  
           delay(1000);        
             }

else{
    digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  
}



//Serial.print(outputValue);
//Serial.print(" ");
//Serial.print(outputValue1);
//Serial.println(" ");




} 
