 #include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int pin = 13;
float time;
float rads = 57.29577951; // 1 radian = approx 57 deg.
float degree = 360;
float frequency = 50;
float nano = 1 * pow (10,-6); // Multiplication factor to convert nano seconds into seconds

// Define floats to contain calculations

float pf;
float angle;
float pf_max = 0;
float angle_max = 0;
int ctr;
const int sensorIn=A0;
int mVperAmp=66;

double Voltage=0;
double VRMS=0;
double AmpsRMS=0;

void setup()
{
 pinMode(pin, INPUT);
 pinMode(6, OUTPUT);
 Serial.begin(9600);
 Serial2.begin(4800);
 lcd.begin(16, 2);
   lcd.print("ANUJ KUMAR");
  lcd.setCursor(0, 1);
  lcd.print("BT16EEE004");
  delay(2000);
  lcd.clear();
    lcd.print("JUNAID ALAM");
  lcd.setCursor(0, 1);
  lcd.print("BT16EEE005");
  delay(2000);
  lcd.clear();
    lcd.print("BHUMIKA MEENA");
  lcd.setCursor(0, 1);
  lcd.print("BT16EEE003");
  delay(2000);
  lcd.clear();
    lcd.print("RITIK SINGH");
  lcd.setCursor(0, 1);
  lcd.print("BT16EEE001");
  delay(2000);
  lcd.clear();
    lcd.print("GUIDED BY");
  lcd.setCursor(0, 1);
  lcd.print("MR HIMESH KUMAR");
  delay(2000);
  lcd.clear();
 
}

void loop()
{
  float price=wifi();
 Serial.println(price);
 lcd.print("CURNT PRC=");
 lcd.setCursor(11, 0);
 lcd.print(price);
 lcd.setCursor(0, 1);
 lcd.print("VidyutPravah.in");
 delay(3000);
   lcd.clear();
  Voltage=getVPP();
VRMS=(Voltage/2.0)*0.707;
AmpsRMS=(VRMS*1000)/mVperAmp;
//Serial.println(AmpsRMS);
lcd.setCursor(0,0);
lcd.print("CURRENT");
lcd.setCursor(9,0);
lcd.print(AmpsRMS);
lcd.setCursor(0,1);
lcd.print("VOLTAGE 230.00");
delay(3000);
lcd.clear();


  
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
  // Serial.println(pf_max, 2);
   float m=fabsf(pf_max);
  // Serial.println(m);
  
   lcd.setCursor(0,0);
   lcd.print("PF=");
   lcd.setCursor(4,0);
   lcd.print(m);
   lcd.print(" ");
   lcd.setCursor(0,1);
   lcd.print("Ph-Shift=");
   lcd.setCursor(10,1);
   lcd.print(angle_max);
   lcd.print(" ");
   delay(3000);
   lcd.clear();
 float z=m*m;
float p=1-z;
float q=AmpsRMS*230*sqrt(p);  
lcd.setCursor(0,0);
lcd.print("ACT PWR");
lcd.setCursor(9,0);
float power=AmpsRMS*230*m;
int powerint=power;
 Serial2.write(powerint);
lcd.print(power);

lcd.setCursor(0,1);
lcd.print("RACT PWR");
lcd.setCursor(9,1);
lcd.print(q);
//Serial.println(AmpsRMS*230*sqrt(p));

delay(3000);
lcd.clear();

time = millis();
float wh=time/3600000;
float kwhPower=power/1000;
float energy=kwhPower*wh;
lcd.setCursor(0, 0);
lcd.print("ENERGY");
  lcd.setCursor(8, 0);
  lcd.print(energy);
  Serial.print("energy");
  Serial.println(energy);
  Serial.print("time ");
  Serial.println(wh);
  //lcd.setCursor(12, 0);
  //lcd.print("kwh");
  
  lcd.setCursor(0, 1);
lcd.print("COST=");
  lcd.setCursor(6, 1);
  float cost=energy*price;
  lcd.print(cost);
   Serial.print("cost");
  Serial.println(cost);
   //lcd.setCursor(10, 1);
//lcd.print("rps");
  delay(3000);
  lcd.clear();

    angle = 0; // Reset variables for next test
   angle_max = 0;
   if (m < 1) // If the calculation is higher than 360 do following...
   {
    digitalWrite(6, HIGH);// Assign the Unity PF to "pf_max"

   }
   else{
    
   digitalWrite(6, LOW);
   }
   //delay(500);
  
}

float getVPP()
{
  float result;
  int readValue;
  int maxValue=0;
  int minValue=1024;

  uint32_t start_time=millis();
  while((millis()-start_time)<1000)
  {
    readValue=analogRead(sensorIn);
    if(readValue>maxValue)
    {
      maxValue=readValue;
    }
    if(readValue<minValue)
    {
      minValue=readValue;
    }
  }
  result=((maxValue-minValue)*5.0)/1024.0;
  return result;
} 
float wifi(){
    while(Serial2.available()>0){
  String payload = Serial2.readString();
  Serial.print("payload ");
  Serial.println(payload);
  float val=payload.toFloat();
return val; 
}
delay(1000);
}
