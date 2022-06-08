/*
// TCS230 color recognition sensor 
// Sensor connection pins to Arduino are shown in comments

Color Sensor      Arduino
-----------      --------
 VCC               5V
 GND               GND
 s0                8
 s1                9
 s2                12
 s3                11
 OUT               10
 OE                GND
*/
const int s0_pin = 8;  
const int s1_pin = 9;  
const int s2_pin = 12;  
const int s3_pin = 11;  
const int out_pin = 10;   
int analogInPin = A1;
int analogInPin1 = A0;
int sensorValue = 0;
int sensorValue1 = 0;
int outputValue = 0;
int outputValue1 = 0;
int transistorPin = 3;
int transistorPin2 = 4;


int statuz = 0;
int tombol100001;
int tombol50001;
const int IRinputPin = 40;;
const int tombol10000 = 24;
const int tombol5000 = 22;
int a;


 #include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

Serial.begin(9600);
pinMode(analogInPin, INPUT);
pinMode(analogInPin1, INPUT);
pinMode(transistorPin, OUTPUT);
pinMode(transistorPin2, OUTPUT);
  pinMode(28, OUTPUT);
  pinMode(30, OUTPUT);

pinMode(2, OUTPUT);
pinMode(7, OUTPUT);
pinMode(tombol10000, INPUT);
pinMode(tombol5000, INPUT);
pinMode(s0_pin, OUTPUT);
pinMode(s1_pin, OUTPUT);
pinMode(s2_pin, OUTPUT);
pinMode(s3_pin, OUTPUT);
pinMode(out_pin, INPUT);
digitalWrite(s0_pin,HIGH);
digitalWrite(s1_pin,LOW);

lcd.init();                      
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.50.000");

 
}


void loop() {

tombol100001 = digitalRead(tombol10000);
tombol50001 = digitalRead(tombol5000);
 //delay(10000);
 

 
digitalWrite(28, HIGH);  
  digitalWrite(30, HIGH);
sensorValue = analogRead(analogInPin);
sensorValue1 = analogRead(analogInPin);
outputValue = map(sensorValue, 0, 1023, 0, 255);
outputValue1 = map(sensorValue1, 0, 1023, 0, 255);

digitalWrite(s2_pin,LOW);
digitalWrite(s3_pin,LOW);
int red_color = pulseIn(out_pin, LOW);
red_color = map(red_color, 25,72,255,0);
delay(50);
digitalWrite(s2_pin,HIGH);
digitalWrite(s3_pin,HIGH);
int green_color = pulseIn(out_pin, LOW);
green_color = map(green_color, 30,90,255,0);
delay(50);
digitalWrite(s2_pin,LOW);

digitalWrite(s3_pin,HIGH);

int blue_color = pulseIn(out_pin, LOW);

blue_color = map(blue_color, 25,70,255,0);

delay(50);


Serial.print("RED: ");

Serial.print(red_color);

Serial.print("  ");

Serial.print("GREEN: ");

Serial.print(green_color);

Serial.print("  ");

Serial.print("BLUE: ");

Serial.print(blue_color);

Serial.println("  ");

//if(red_color<=260 && red_color >190 && green_color<235 && green_color>200 && blue_color<220 && blue_color>153 ){
//if(red_color>-173 && red_color<28 && green_color>-34 && green_color<-10  && blue_color>38 && blue_color<108){  
  if(red_color<-124){  
  a=1;
  Serial.println("uang 50000");
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  lcd.clear();
  lcd.print("Pilih Nominal");
  lcd.setCursor(0,1);
  lcd.print("Rp.10000/Rp.5000");
  
  
  //digitalWrite(6, HIGH);
  
}



else if(tombol100001 == HIGH ){
Serial.println("SILAHKAN PILIH PECAHAN YANG DI INGINKAN");    
  lcd.clear();
  lcd.print("Rp.10.000");
  lcd.setCursor(0,1);
  lcd.print("");
  analogWrite(transistorPin, outputValue);
digitalWrite(28, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, LOW);

           delay(6000);        

   analogWrite(transistorPin, 0);
digitalWrite(28, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, LOW);

             }

else if(tombol50001 == HIGH ){
Serial.println("SILAHKAN PILIH PECAHAN YANG DI INGINKAN");    
  lcd.clear();
  lcd.print("Rp.5000");
  lcd.setCursor(0,1);
  lcd.print("");
analogWrite(transistorPin2, outputValue1);
  digitalWrite(28, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, HIGH);
           delay(16000); 
              analogWrite(transistorPin2, 0);
digitalWrite(28, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(30, LOW);
       
             }

/*else if(red_color>90 && red_color<162 && green_color>110 && green_color<150  && blue_color>124 && blue_color<170){  
  Serial.println("uang 2000");
                // wait for a second
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(6, HIGH);
  delay(1000);
  */
//}
else{
    digitalWrite(2, HIGH);    // turn the LED off by making the voltage LOW
  //digitalWrite(6, LOW);  
}
//else if (red_color<210 && red_color >190 && green_color<210 && green_color>195 && blue_color<210 && blue_color>183 ) {
  //Serial.println("uang 2000");
//}
delay(1000);

}
