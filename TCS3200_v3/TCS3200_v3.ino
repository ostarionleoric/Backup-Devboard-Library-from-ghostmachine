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

void setup() {

Serial.begin(9600);
 pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
pinMode(s0_pin, OUTPUT);

pinMode(s1_pin, OUTPUT);

pinMode(s2_pin, OUTPUT);

pinMode(s3_pin, OUTPUT);

pinMode(out_pin, INPUT);

digitalWrite(s0_pin,HIGH);

digitalWrite(s1_pin,LOW);

}


void loop() {

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
if(red_color>120 && red_color<190 && green_color>100 && green_color<150  && blue_color>70 && blue_color<105){  
  Serial.println("uang 5000");
                // wait for a second
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(6, HIGH);
  delay(1000);
}
else if(red_color>90 && red_color<160 && green_color>110 && green_color<150  && blue_color>124 && blue_color<170){  
  Serial.println("uang 2000");
                // wait for a second
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(6, HIGH);
  delay(1000);
}else{
    digitalWrite(7, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(6, LOW);  
}
//else if (red_color<210 && red_color >190 && green_color<210 && green_color>195 && blue_color<210 && blue_color>183 ) {
  //Serial.println("uang 2000");
//}
delay(1000);

}
