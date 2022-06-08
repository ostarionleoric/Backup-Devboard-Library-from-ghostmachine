/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#include <Servo.h>
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

int pos = 0; 
Servo myservo; 
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
   myservo.attach(9);
     pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
    buttonState = digitalRead(buttonPin);
Serial.println(buttonState);
 if (buttonState == HIGH) {
    // turn LED on:
     myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(2000);                                  // wait for a second
      myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(2000);                      // wait for a second
 }
 else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
 
}
