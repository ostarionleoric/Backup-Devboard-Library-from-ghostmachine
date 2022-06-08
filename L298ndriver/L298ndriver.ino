int in1 = 9; //Declaring the pins where in1 in2 from the driver are wired 
int in2 = 8; //here they are wired with D9 and D8 from Arduino
int ConA = 10; //And we add the pin to control the speed after we remove its jumper 
               //Make sure it's connected to a pin that can deliver a PWM signal


void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT); //Declaring the pin modes, obviously they're outputs
  pinMode(in2, OUTPUT);
  pinMode(ConA, OUTPUT);
}

void TurnMotorA(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ConA,250);
}

void TurnOFFA(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(ConA,250);
}
void TurnMotorA2(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ConA,250);
}
void loop() {
  // put your main code here, to run repeatedly:
  TurnMotorA();  //Sequence: turning on low speed, stop, turning again in high speed and stop



}
