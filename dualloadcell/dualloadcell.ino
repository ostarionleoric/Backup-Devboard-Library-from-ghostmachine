#include "HX711.h"
#include <Servo.h>

Servo myservo;
#define DOUT  A0
#define CLK  A1
#define DOUT2  A2
#define CLK2  A3



HX711 scale(DOUT, CLK);
HX711 scale2(DOUT2, CLK2);
float calibration_factor = 219.90;
int GRAM;
int GRAM2;


void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
  scale2.set_scale();
  scale2.tare();
  myservo.attach(9); 
}

void loop() {
  scale.set_scale(calibration_factor);
  scale2.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
  GRAM2 = scale2.get_units(), 4;
  Serial.print("timbagan satu :");
  Serial.println(GRAM);
  delay(500);
  Serial.print("timbagan dua :");
  Serial.println(GRAM2);
  delay(500);
  Serial.print("TOTAL BERAT :");
  Serial.println(GRAM+GRAM2);
  
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
