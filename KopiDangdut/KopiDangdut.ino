//library servo
#include <Servo.h>
Servo servoKopi; 


//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//library sensor berat
#include "HX711.h"
#define DOUT  A0
#define CLK  A1
HX711 scale(DOUT, CLK);
float calibration_factor = 300;  /// default 344.10;
int gram;
int buttonState = 0;
const int tombolStart = 22;
const int tombolStop = 24;
int relayBubuk = 10;
int relayConveyor = 11;
int relayHeater1 = 12;
int relayHeater2 = 13;

int detekbungkus;


void setup() {
servoKopi.attach(9);
Serial.begin(9600);
scale.set_scale();
scale.tare();

pinMode(tombolStart, INPUT);
pinMode(tombolStop, INPUT);
pinMode(relayBubuk, OUTPUT);
pinMode(relayConveyor, OUTPUT);
pinMode(relayHeater1, OUTPUT);
pinMode(relayHeater2, OUTPUT);

}

void loop() {
  
  scale.set_scale(calibration_factor);
  gram = scale.get_units(), 4;
  Serial.println(gram);
  digitalWrite(relayHeater1,HIGH);
  digitalWrite(relayHeater2,HIGH);
  
  
  buttonState = digitalRead(tombolStart);
  if (digitalRead(tombolStart)==HIGH){
    if (buttonState==0) {            
      buttonState=1;
      digitalWrite(relayConveyor,HIGH);                 
      delay(5000);
      digitalWrite(relayBubuk,HIGH);    
      delay(180000);
      }                          
    else {                       
      buttonState=0;
                
      digitalWrite(relayBubuk,LOW);     
    }
  delay(1000);                   
  }
 else if(gram >450){
servoKopi.write(180);          
delay(100);
servoKopi.write(0);            
delay(5000);
digitalWrite(relayConveyor,HIGH);                 
delay(5000);
  }
  else if(digitalRead(tombolStart)==HIGH){
digitalWrite(relayConveyor,LOW);  
digitalWrite(relayBubuk,LOW);       
digitalWrite(relayHeater1,LOW);
digitalWrite(relayHeater2,LOW);
  
  }
}
