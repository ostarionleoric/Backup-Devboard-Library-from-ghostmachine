#define TRIGGER_PIN 3
#define ECHO_PIN 5
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250
const int infrared = 4; 
const int s0_pin = 8;  
const int s1_pin = 9;  
const int s2_pin = 12;  
const int s3_pin = 11;  
const int out_pin = 10;   
const int pinMotorDuit1 = 7;          
const int pinMotorDuit2 = 6;
const int button1 = 22;            
const int button2 = 23;
const int led =13;                
const int relayMesinAir =26;
int ledflag=0;                   
const int PinSensorWaterFlowTaman=2;
float flow_countertaman,liter;

boolean batasAir22=HIGH;
boolean batasAir10=LOW;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


void setup() {
//PIN SENSOR ULTRASONIK
   pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(500);
   Serial.begin(9600);
   
//PIN UNTUK MOTOR NAREK DUITNYA
pinMode(pinMotorDuit1, OUTPUT);
pinMode(pinMotorDuit2, OUTPUT);

//PIN UNTUK SENSOR WARNA
pinMode(s0_pin, OUTPUT);
pinMode(s1_pin, OUTPUT);
pinMode(s2_pin, OUTPUT);
pinMode(s3_pin, OUTPUT);
pinMode(out_pin, INPUT);
digitalWrite(s0_pin,HIGH);
digitalWrite(s1_pin,LOW);

//LCD
lcd.init();                      
lcd.backlight();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Masukkan uang");
lcd.setCursor(0,1);
lcd.print("Rp.5000/Rp.2000");


  
//PIN SENSOR AIR/WATERFLOW
pinMode(PinSensorWaterFlowTaman, INPUT);
digitalWrite(PinSensorWaterFlowTaman, HIGH);
attachInterrupt(0, flowtaman, RISING);

//PIN UNTUK STOP KONTAK MESIN AIR
pinMode(led,OUTPUT);           
pinMode(relayMesinAir, OUTPUT);


digitalWrite(led,LOW);         
digitalWrite(relayMesinAir, HIGH); 
}

void loop() {


delay(MEASURE_DELAY);
long distance = measure();
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" mm");
int mililiter = liter * 1000;
Serial.println(liter);
Serial.print("MILILITER = ");
Serial.println(mililiter);



  
// KODE PEMBACAAN WARNA
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


//RANGE WARNA UNTUK PENGENALAN UANG 5000
int duitlimaribu = red_color>90 && red_color<120 && green_color>50 && green_color<90  && blue_color>10 && blue_color<30;

//RANGE WARNA UNTUK PENGENALAN UANG 2000
int duitduaribu = red_color>15 && red_color<55 && green_color>45 && green_color<85  && blue_color>55 && blue_color<100;
int duit;

//PENGENALAN UANG 5000 BESERTA PENGECEKAN STOK AIR DALAM TANGKI
if(duitlimaribu && distance<600){  
  Serial.println("uang 5000");
  digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, HIGH);
  delay(2000);
  digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, LOW);

//MENAMPILKAN UANG 5000 PADA LCD JIKA UANG SUKSES TERBACA OLEH SENSOR
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RP. 5000");
  lcd.setCursor(2,1);
  lcd.print("22 Liter");
  digitalWrite(relayMesinAir, HIGH);
  delay(2000);
  flow_countertaman=0;
  
//MENGHIDUPKAN POMPA AIR JIKA TERDETEKSI UANG 5000  
  digitalWrite(relayMesinAir, LOW); 
  batasAir22=LOW;
}


//PENGENALAN UANG 2000
else if(duitduaribu && distance<600){  
  Serial.println("uang 2000");
  digitalWrite(pinMotorDuit1, LOW);   
  digitalWrite(pinMotorDuit2, HIGH);
  delay(2000);


//MENAMPILKAN UANG 2000 PADA LCD JIKA UANG SUKSES TERBACA OLEH SENSOR
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RP. 2000");
  lcd.setCursor(0,1);
  lcd.print("10 Liter");
  flow_countertaman=0;

//MENGHIDUPKAN POMPA AIR JIKA TERDETEKSI UANG 5000
  digitalWrite(relayMesinAir, LOW); 
  batasAir10=HIGH;

}

//batas air untuk uang 2000 dalam satual mililiter (1000 = 1 Liter)
else if(batasAir10 == HIGH && mililiter >=10000){
  digitalWrite(relayMesinAir, HIGH); 
  batasAir10 == LOW;
  flow_countertaman=0;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Masukkan uang");
  lcd.setCursor(0,1);
  lcd.print("Rp.5000/Rp.2000");
}

//batas air untuk uang 5000 dalam satual mililiter (1000 = 1 Liter)
else if(batasAir22 == LOW && mililiter >=22000){
  digitalWrite(relayMesinAir, HIGH); 
  batasAir22 == HIGH;
  flow_countertaman=0;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Masukkan uang");
  lcd.setCursor(0,1);
  lcd.print("Rp.5000/Rp.2000");
}

//PEMBACAAN STOK AIR DALAM TANGKI DENGAN ULTRASONIC
else if(distance>900) {
        digitalWrite(relayMesinAir, HIGH); 
}
else{
  digitalWrite(pinMotorDuit1, LOW);
  digitalWrite(pinMotorDuit2, LOW);  
}
}


//FUNGSI KONVERSI ALIRAN AIR PADA SENSOR KEDALAM SATUAN LITER
void flowtaman() 
    {
      flow_countertaman++;
       liter=flow_countertaman/350;
}


//FUNGSI PENGUKURAN TINGGI AIR DALAM TANGKI
long measure()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement();
  }
  return measureSum / MEASURE_SAMPLES;
}


//FUNGSI PENGUKURAN TINGGI AIR DALAM TANGKI
long singleMeasurement()
{
  long duration = 0;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(11);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}
