#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Pin arduino yang dipake tiap tiap modul tambahannya, contoh: proximity, Inframerah, relay, motor driver 
const int sensorLogam = 7; //pin Sensor proximity
const int pistonPress =  2; //pin relay keran pneumatic
const int pininframerah =  6; //pin inframerah
const int motorKoin =  3;
const int pinMotorCoin =  12; //pin motor dc untuk pelontar koin
const int pinMotorCoin2 =  13;
const int pinKecepatan =  9; //pin PWM untuk mengontrol kecepatan motor



int deteksikaleng = 0;
int deteksikalenggepeng = 0;
int a=0;
LiquidCrystal_I2C lcd(0x27,20,4);
void setup()
{
  pinMode(sensorLogam, INPUT); //deklarasi sensor proximity digunakan sebagai input oleh arduino
  pinMode(pininframerah, INPUT); //deklarasi sensor inframerah digunakan sebagai input oleh arduino
  pinMode(pistonPress, OUTPUT); //deklarasi relay digunakan sebagai output oleh arduino
  pinMode(motorKoin, OUTPUT); 
  pinMode(pinMotorCoin, OUTPUT);//deklarasi Motor DC digunakan sebagai output oleh arduino
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
 /*
  lcd.setCursor(6,0);
  lcd.print("SILAHKAN");
  lcd.setCursor(8,1);
  lcd.print("AMBIL");
  lcd.setCursor(8,2);
  lcd.print("KOIN");
  lcd.setCursor(1,3);
  lcd.print("TEURIMONG GEUNASEH");
 */ 
  digitalWrite(pistonPress, LOW);
  digitalWrite(motorKoin, LOW);
  analogWrite(pinKecepatan, 80);//deklarasi kecepatan putar motor DC, range satuan yang digunakan bekisar dari 0 sampai 255
}
void loop()
{
deteksikaleng = digitalRead(sensorLogam); //membaca apakah di dalam alat ada kaleng
Serial.println(deteksikaleng);
deteksikalenggepeng = digitalRead(pininframerah);// membaca kondisi kaleng sudah berhasil di press dan keluar dari tempat kaleng
Serial.print("IR =");
Serial.println(deteksikalenggepeng);
if(deteksikaleng == LOW){//jika kaleng terdeteksi oleh sensor logam
a=1;
        
    delay(1000);//tunggu satu detik
    digitalWrite(pistonPress, LOW);
    delay(1000);
    digitalWrite(pistonPress, HIGH);//maka hidupkan relay press pneumatic
    delay(5000);
}
if(deteksikalenggepeng == LOW && a ==1){ //jika kaleng yang berhasil di press keluar dari lubang keluaran kaleng dan terdeteksi oleh sensor inframerah
  lcd.clear();

  //tampilkan tulisan "SILAHKAN AMBIL KOIN" ke LCD
  lcd.setCursor(6,0);
  lcd.print("SILAHKAN");
  lcd.setCursor(7,1);
  lcd.print("AMBIL");
  lcd.setCursor(7,2);
  lcd.print("KOIN");
  lcd.setCursor(1,3);
 // lcd.print("TEURIMONG GEUNASEH");
  delay(200);

  lcd.setCursor(1,3);
  lcd.print("TEURIMONG GEUNASEH");
    delay(200);
  digitalWrite(pinMotorCoin, HIGH); //maka hidupkan Motor DC pelontar koin
  delay(200);
  digitalWrite(pinMotorCoin, LOW);
  delay(2500);
  a=0;
}
else {
  digitalWrite(pistonPress, HIGH);
  lcd.setCursor(6,0);
  lcd.print("SILAHKAN");
  lcd.setCursor(6,1);
  lcd.print("MASUKKAN");
  lcd.setCursor(7,2);
  lcd.print("KALENG");
  lcd.setCursor(1,3);
  lcd.print("                   ");
}
}
