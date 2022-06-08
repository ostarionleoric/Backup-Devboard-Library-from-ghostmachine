#include "HX711.h"
#include <Servo.h>

Servo myservo;
#define DOUT  A1
#define CLK  A0
HX711 scale(DOUT, CLK);
float calibration_factor = 219.90;
int GRAM;

void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
  myservo.attach(9); 
}

void loop() {
  scale.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
  
  Serial.println(GRAM);

  if(GRAM>100){
    GRAM= 0;
     myservo.write(130);
  delay(2000);
  myservo.write(0);
  delay(100);
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);
  
  myservo.write(10);
  delay(50);
  myservo.write(0);
  delay(50);

  
  }
  else{
    myservo.write(130);
  }
  GRAM= 0;
}
