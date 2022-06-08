#include "EmonLib.h"

unsigned long interval=1000; // the time we need to wait
unsigned long interval1=1000;
unsigned long previousMillis=0;

EnergyMonitor emon1;
//int pin_sct = A1;
int nilaixor;
int m;// initialise variable m
float n;//initialise variable n
float vrms;
float sinpi;

float P;
float Q;
float S;


int pinpanse = 1;
float pin = 9;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6);

float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
int ctr;

float angle_abs = 0;


void setup()
{
  pinMode(12, OUTPUT);
  pinMode(pin, INPUT);
  pinMode(A0,INPUT); // set pin a0 as input pin
  //pinMode(9,INPUT); // set pin a0 as input pin
  Serial.begin(9600);// begin serial communication between arduino and pc
   emon1.current(1, 8); 
}

void loop()
{
   unsigned long currentMillis = millis();
      double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  nilaixor=digitalRead(9);

  m=analogRead(A0);// read analog values from pin A0 across capacitor
   //n=(m* .304177);// converts analog value(x) into input ac supply value using this formula ( explained in woeking section)
  n=(m* .430107);
vrms=n/sqrt(2);  

  for (ctr = 0; ctr <= 4; ctr++) // Perform 4 measurements then reset
  {
  // 1st line calculates the phase angle in degrees from differentiated time pulse
  // Function COS uses radians not Degree's hence conversion made by dividing angle / 57.2958
   angle = ((((pulseIn(pin, HIGH)) * nano)* degree)* frequency);
  // pf = cos(angle / rads); 
   
   if (angle > angle_max) // Test if the angle is maximum angle
     {
      angle_max = angle; // If maximum record in variable "angle_max"
      pf_max = cos(angle_max / rads); // Calc PF from "angle_max"
       
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
   //Serial.print(angle_max, 2); // Print the result
   //Serial.print(",");
   //Serial.println(pf_max, 2);
   sinpi = sin(angle_max / rads);  
  // Serial.print(angle_max, 2); // Print the result
  // Serial.print(",");
   //Serial.println(pf_max, 2);
   


   Serial.print("PF=");
   Serial.print(abs(pf_max));
   Serial.println(" ");
      Serial.print("P=");
   Serial.print((vrms*Irms)*pf_max);
   Serial.print("VAR ");
   Serial.println(" ");
   Serial.print("Q=");
   Serial.print((vrms*Irms)*sinpi);
   Serial.print("VAR ");
   Serial.println(" ");
  Serial.print("S=");
   Serial.print(vrms*Irms);
   Serial.print("VA ");
   Serial.println(" ");

  Serial.print("Nilai Sinpi=");
   Serial.print(sinpi);
   Serial.print(" ");
   Serial.println(" ");

   P=(vrms*Irms)*pf_max;
   Q=(vrms*Irms)*sinpi;
   S=vrms*Irms;
     Serial.print("Nilai Kospinya=");
     
   //Serial.print(((vrms*Irms)*pf_max)/((vrms*Irms)*sinpi));
   Serial.print(P/S);
   Serial.print(" ");
   Serial.println(" ");

      
   Serial.print("Ph-Shift=");
   
   Serial.print(angle_max);
   Serial.print(" ");

   
   //delay(500);
   angle = 0; // Reset variables for next test
   angle_max = 0;

   Serial.print("   ZeroCross input  " ) ; // specify name to the corresponding value to be printed
   Serial.print(nilaixor) ; // print input analog value on serial monitor
   Serial.print("   analaog input  " ) ; // specify name to the corresponding value to be printed
   Serial.print(m) ; // print input analog value on serial monitor
   Serial.print("   ac voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(n) ; // prints the ac value on Serial monitor
   Serial.print("   ac RMS voltage  ") ; // specify name to the corresponding value to be printed
   Serial.print(vrms) ; // prints the ac value on Serial monitor
     Serial.print("   Arus yang terbaca : ");
  Serial.print(Irms);
   
   Serial.println(" ");
   Serial.println(" ");
   pinpanse = 0;
      if( abs(pf_max) <= 0.7){
    digitalWrite(12, HIGH);
   }
   else if( abs(pf_max) >= 0.9) {
    digitalWrite(12, LOW);
   }
   else {
    
   // pinpanse = 1;
 //  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      // turn the LED on (HIGH is the voltage level)
  //;
  // previousMillis = millis();
  //}

    //  if ((unsigned long)(currentMillis - previousMillis) >= interval1) {
        // turn the LED off by making the voltage LOW
    //delay(1000);
  //previousMillis = millis();
}
}
