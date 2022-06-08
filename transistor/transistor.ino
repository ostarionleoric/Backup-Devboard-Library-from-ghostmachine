int pushButton = 2;

// the transistor which controls the motor will be attached to digital pin 9
int motorControl = 9;

// the setup routine runs once when you press reset:
void setup() {
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  // make the transistor's pin an output:
  pinMode(motorControl, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {

  // read the state of the button and check if it is pressed
 // if(digitalRead(pushButton) == HIGH){
    // ramp up the motor speed
    //for(
      int x = 250;// x <= 255; x++){
      analogWrite(motorControl, x);
      delay(50);

}
