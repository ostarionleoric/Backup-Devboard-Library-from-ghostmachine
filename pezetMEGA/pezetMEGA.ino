#include <PZEM004T.h>

#include <SoftwareSerial.h> // Arduino IDE <1.6.6


//#include <LiquidCrystal.h>

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

PZEM004T pzem(3,2);  // (RX,TX) connect to TX,RX of PZEM

IPAddress ip(192,168,1,1);


void setup() {

  Serial.begin(9600);

  pzem.setAddress(ip);
  //lcd.begin(16, 2); // lcd rows and columns

  
}


void loop() {
 


  float v = pzem.voltage(ip);

  if (v < 0.0) v = 0.0;

  Serial.print(v);Serial.print("V; ");
 Serial.println(" ");
 // lcd.setCursor(0,0);
 // lcd.print("V= ");
  //lcd.setCursor(2,0);
  //lcd.print(v);


  float i = pzem.current(ip);

  if (i < 0.0) i = 0.0;

  Serial.print(i);Serial.print("A; ");
Serial.println(" ");
  //lcd.setCursor(9,0);
  //lcd.print("A= ");
  //lcd.setCursor(11,0);
  //lcd.print(i);




  float p = pzem.power(ip);

  if (p < 0.0) p = 0.0;


  Serial.print(p);Serial.print("W; ");
Serial.println(" ");
//  lcd.setCursor(9,1);
  //lcd.print("W= ");
  //lcd.setCursor(11,1);
  //lcd.print(p);




  float e = pzem.energy(ip);

  Serial.print("PF= ");Serial.print((p)/(v*i));
Serial.println(" ");
  //lcd.setCursor(0,1);
  //lcd.print("PF=");
  //lcd.setCursor(3,1);
  //lcd.print((p)/(v*i));

 
  Serial.println();

  delay(100);
}
