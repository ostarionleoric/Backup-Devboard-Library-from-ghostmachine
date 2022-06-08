#include "HX711.h"
#include <Servo.h>

Servo myservo;
#define DOUT  A0
#define CLK  A1
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
  delay(500);

 /** if(GRAM>100){
    GRAM= 0;
     myservo.write(90);
  delay(5000);
  myservo.write(0);
  delay(1000);
  
  
  }
  else{
    myservo.write(90);
  }
  GRAM= 0;
  **/
}
