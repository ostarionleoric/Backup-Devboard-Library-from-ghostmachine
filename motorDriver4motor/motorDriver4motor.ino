// the transistor which controls the motor will be attached to digital pin 9
#include <Wire.h>
float Volt1;
float Volt;

int motorControl = 9;
int motorControl2 = 8;

// the setup routine runs once when you press reset:
void setup() {
  // make the pushbutton's pin an input:
//  pinMode(pushButton, INPUT);

  // make the transistor's pin an output:
  Serial.begin(9600);
  pinMode(motorControl, OUTPUT);  
   pinMode(motorControl2, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
Volt1=analogRead(0);
      Volt=((Volt1*0.00489)*5);
      Serial.print(Volt);
      Serial.println("V");
     
  // read the state of the button and check if it is pressed
 /// if(digitalRead(pushButton) == HIGH){
    // ramp up the motor speed
    //for(int x = 0; x <= 255; x++){
      
      analogWrite(motorControl, 180);
      //Serial.println(x);
      delay(50);
      //digitalWrite(motorControl2, LOW);
    //}

    // ramp down the motor speed
   //for(int x = 255; x >= 0; x--){
     // analogWrite(motorControl, x);
      //Serial.println(x);
      //delay(50);
   //}    
  //}

  delay(1);        // delay in between reads for stability
}
