//library servo
#include <Servo.h>
Servo servoKiri; 
Servo servoTengah; 
Servo servoKanan; 

//LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display




//pin yang dipake TCS
const int s0_pin = 8;  
const int s1_pin = 9;  
const int s2_pin = 12;  
const int s3_pin = 11;  
const int out_pin = 10;   

//pin tombol

const int tombolKanan = 22;
const int tombolTengah = 24;
const int tombolKiri = 26;

int duitmasuk=0;
int duitlimaribu;
int kananState = 0;
int tengahState = 0;
int kiriState = 0;


void setup() {
Serial.begin(9600);

servoKiri.attach(5);
servoTengah.attach(6);
servoKanan.attach(7);


pinMode(tombolKanan, INPUT);
pinMode(tombolTengah, INPUT);
pinMode(tombolKiri, INPUT);


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
lcd.print("Rp.5000");


}

void loop() {

int red_color = pulseIn(out_pin, LOW);
int green_color = pulseIn(out_pin, LOW);
int blue_color = pulseIn(out_pin, LOW);


digitalWrite(s2_pin,LOW);
digitalWrite(s3_pin,LOW);

red_color = map(red_color, 25,72,255,0);
delay(50);
digitalWrite(s2_pin,HIGH);
digitalWrite(s3_pin,HIGH);

green_color = map(green_color, 30,90,255,0);
delay(50);
digitalWrite(s2_pin,LOW);
digitalWrite(s3_pin,HIGH);

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
duitlimaribu = red_color>90 && red_color<120 && green_color>50 && green_color<90  && blue_color>10 && blue_color<30;

kananState = digitalRead(tombolKanan);
tengahState = digitalRead(tombolTengah);
kiriState = digitalRead(tombolKiri);
if(duitlimaribu){
  duitmasuk=1;
  Serial.println("uang 50000");
  digitalWrite(20, LOW);   
  delay(1000);
  lcd.clear();
  lcd.print("Pilih Minuman");
  lcd.setCursor(0,1);
  lcd.print("Fanta/Cocacola/Sprite");
     
}
else if(kananState == HIGH && duitmasuk == 1){

lcd.clear();
lcd.print("Fanta");
lcd.setCursor(0,1);
lcd.print("");
servoKanan.write(180);          
delay(100);
servoKanan.write(0);            
delay(100);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.5000");

duitmasuk=0;
}
else if(tengahState == HIGH && duitmasuk == 1){

lcd.clear();
lcd.print("Cocacola");
lcd.setCursor(0,1);
lcd.print("");
servoTengah.write(180);          
delay(100);
servoTengah.write(0);            
delay(100);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.5000");


duitmasuk=0;
}
else if(kiriState == HIGH && duitmasuk == 1){

lcd.clear();
lcd.print("Sprite");
lcd.setCursor(0,1);
lcd.print("");
servoKiri.write(180);          
delay(100);
servoKiri.write(0);            
delay(100);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.5000");


duitmasuk=0;
}
else{
  //mager bet hari minggu :P
}

}
