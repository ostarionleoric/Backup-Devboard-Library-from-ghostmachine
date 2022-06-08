int pin = 13;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6); // Multiplication factor to convert nano seconds into seconds
float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
int ctr;

void setup() {
  
  Serial.begin(9600);
  pinMode(13, INPUT);
  

}

void loop() {
 // for (ctr = 0; ctr <= 10; ctr++) // Perform 4 measurements then reset
  //{
  // 1st line calculates the phase angle in degrees from differentiated time pulse
  // Function COS uses radians not Degree's hence conversion made by dividing angle / 57.2958
   angle = ((((pulseIn(pin, HIGH)) * nano)* degree)* frequency);
   pf = cos(angle / rads); 
   
   if (angle > angle_max) // Test if the angle is maximum angle
     {
      angle_max = angle; // If maximum record in variable "angle_max"
      pf_max = cos(angle_max / rads); // Calc PF from "angle_max"
     }
  // }
   if (angle_max > 360) // If the calculation is higher than 360 do following...
   {
    angle_max = 0; // assign the 0 to "angle_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   if (angle_max == 0) // If the calculation is higher than 360 do following...
   {
    angle_max = 0; // assign the 0 to "angle_max"
    pf_max = 1; // Assign the Unity PF to "pf_max"
   }
   Serial.print("Faktor daya=");
   //lcd.setCursor(4,0);
   Serial.print(pf_max);
   Serial.println(" ");
   //lcd.setCursor(0,1);
   Serial.print("Ph-Shift=");
   //lcd.setCursor(10,1);
   Serial.print(angle_max);
   Serial.println(" ");
     angle = 0; // Reset variables for next test
   angle_max = 0;
  //read the pushbutton value into a variable
 // int sensorVal = digitalRead(13);
  //print out the value of the pushbutton
  //Serial.println(sensorVal);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  //if (sensorVal == HIGH) {
   // digitalWrite(13, LOW);
   //Serial.println("Satu");
  //} else {
    //digitalWrite(13, HIGH);
    //Serial.println("kosong");
  //}
}
