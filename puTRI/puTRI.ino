//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pin = 13;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6); // Multiplication factor to convert nano seconds into seconds

// Define floats to contain calculations

float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
float pieliedie;
float pieliedie2;

int ctr;

void setup()
{
 pinMode(pin, INPUT_PULLUP);
 Serial.begin(9600);
// lcd.begin(16, 2);
}

void loop()
{
  
for (ctr = 0; ctr <= 5; ctr++) // Perform 4 measurements then reset
  {
  // 1st line calculates the phase angle in degrees from differentiated time pulse
  // Function COS uses radians not Degree's hence conversion made by dividing angle / 57.2958
   angle = ((((pulseIn(pin, HIGH)) * nano)* degree)* frequency);
   //pieliedie = angle/rads;
   pieliedie = angle*(3.14/180);
   pf = cos(pieliedie); 
   
   if (angle > angle_max) // Test if the angle is maximum angle
     {
      angle_max = angle; // If maximum record in variable "angle_max"
      //pieliedie2=angle_max / rads;
      pieliedie2=angle_max *(3.14/180);
      pf_max = cos(pieliedie2); // Calc PF from "angle_max"
     }
   }
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
   Serial.print(angle_max, 2); // Print the result
   Serial.print(",");
   Serial.println(pf_max, 2);
  //lcd.clear();
   //lcd.setCursor(0,0);
   Serial.print("Faktor daya=");
   //lcd.setCursor(4,0);
   Serial.print(pf_max);
   Serial.print(" ");
   //lcd.setCursor(0,1);
   Serial.print("Ph-Shift=");
   //lcd.setCursor(10,1);
   Serial.print(angle_max);
   Serial.print(" ");
   
   //delay(500);
   angle = 0; // Reset variables for next test
   angle_max = 0;
}
