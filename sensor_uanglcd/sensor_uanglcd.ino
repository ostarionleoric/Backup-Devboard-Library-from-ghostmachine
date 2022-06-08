//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

const int s0 = 8;  
const int s1 = 9;  
const int s2 = 12;  
const int s3 = 11;  
const int out = 10;   


// LED pins connected to Arduino
int Red=0, Blue=0, Green=0;  //RGB values 

void setup() {
  lcd.init();
   lcd.backlight();
      pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
}

void loop(){
  
  GetColors();                                     //Execute the GetColors function to get the value of each RGB color
  
  
                    //Depending of the RGB values given by the sensor we can define the color and displays it on the monitor

  if (Red <=15 && Green <=15 && Blue <=15){         //If the values are low it's likely the white color (all the colors are present)
      Serial.println("White");
             lcd.setCursor(0,0);
      lcd.print("Masukkan Uang . . .");                    
  lcd.setCursor(0,1);
      lcd.print("yang sesuai . . .");
  }
  else if (Red<Blue && Red<=Green && Red<23){      //if Red value is the lowest one and smaller thant 23 it's likely Red
  
      Serial.println("Red");
      lcd.setCursor(0,0);
      lcd.print("uang 10.000");
  }
  
  else if (Blue<Green && Blue<Red && Blue<20){    //Same thing for Blue
      Serial.println("Blue");
            lcd.setCursor(0,0);
      lcd.print("uang 50.000");
      }

  else if (Blue<Red && Green-Blue > 20  && Green-Blue<= 200){           //Green it was a little tricky, you can do it using the same method as above (the lowest), but here I used a reflective object
      Serial.println("UANG 5000"); 
      lcd.setCursor(0,0);
      lcd.print("uang 5000");
      }          //which means the blue value is very low too, so I decided to check the difference between green and blue and see if it's acceptable
            
  else{
     Serial.println("Unknown");                  //if the color is not recognized, you can add as many as you want
        lcd.setCursor(0,0);
      lcd.print("Masukkan Uang . . .");
  }

  delay(2000);                                   //2s delay you can modify if you want
  lcd.clear();
  

 // lcd.setCursor(0,1);
 // lcd.print("KelasRobot.com");
}
void GetColors()  
{    
  digitalWrite(s2, LOW);                                           //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green 
  digitalWrite(s3, LOW);                                           
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again, if you have trouble with this expression check the bottom of the code
  delay(20);  
  digitalWrite(s3, HIGH);                                         //Here we select the other color (set of photodiodes) and measure the other colors value using the same techinque
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  
  digitalWrite(s2, HIGH);  
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  
}
