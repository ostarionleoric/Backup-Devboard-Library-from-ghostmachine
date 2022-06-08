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
const int pinMotorDuit1 = 7;            // GPIO 8 for the button
const int pinMotorDuit2 = 6;
const int button1 = 22;            // GPIO 8 for the button
const int button2 = 23;
const int led =13;                // GPIO 7 for the LED
const int relayMesinAir =26;
int ledflag=0;                   // LED status flag
const int PinSensorWaterFlowTaman=2;// intr 0 // pin 2
float flow_countertaman,liter;

boolean batasAir22=HIGH;
boolean batasAir10=LOW;

 #include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display




void setup() {
  // put your setup code here, to run once:
     pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);

   // Reset the trigger pin and wait a half a second
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
attachInterrupt(0, flowtaman, RISING); // Setup Interrupt 0 pada pin 2

//TOMBOL DUIT 5000 
pinMode(button1,INPUT);

//TOMBOL DUIT 2000
pinMode(button2,INPUT);


pinMode(led,OUTPUT);           // define LED as an output
pinMode(relayMesinAir, OUTPUT);

 //pinMode(pinMotorDuit1, OUTPUT);
  //pinMode(pinMotorDuit2, OUTPUT);
digitalWrite(led,LOW);         // turn output off just in case
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
/*
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(mililiter);
  lcd.setCursor(2,1);
*/
  
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
int duitlimaribu = red_color>120 && red_color<190 && green_color>100 && green_color<150  && blue_color>70 && blue_color<105;
int duitduaribu = red_color>90 && red_color<160 && green_color>110 && green_color<150  && blue_color>124 && blue_color<170;
int duit;

//PENGENALAN UANG 5000
if(duitlimaribu && distance<600){  
  Serial.println("uang 5000");
  digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, HIGH);
  delay(2000);
  digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, LOW);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RP. 5000");
  lcd.setCursor(2,1);
  lcd.print("22 Liter");

    //batasAir10=LOW;

  digitalWrite(relayMesinAir, HIGH);
  delay(2000);
  flow_countertaman=0;
  digitalWrite(relayMesinAir, LOW); 
    batasAir22=LOW;
}


//PENGENALAN UANG 2000
else if(duitduaribu && distance<600){  
  Serial.println("uang 2000");
                // wait for a second
    digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, HIGH);
  delay(2000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RP. 2000");
  lcd.setCursor(0,1);
  lcd.print("10 Liter");
  flow_countertaman=0;
  digitalWrite(relayMesinAir, LOW); 
batasAir10=HIGH;

}

//batas air untuk uang 5000
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

//batas air untuk uang 5000
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
else if(distance>900) {
        digitalWrite(relayMesinAir, HIGH);    // turn the LED off by making the voltage LOW
  }
  //else{
    //digitalWrite(relayMesinAir, HIGH);
  //}

else{
  digitalWrite(pinMotorDuit1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(pinMotorDuit2, LOW);  
}

 
//delay(1000);

}


void flowtaman () // Interrupt function taman
    {
      flow_countertaman++;
       liter=flow_countertaman/350;
}
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
long singleMeasurement()
{
  long duration = 0;
  // Measure: Put up Trigger...
  digitalWrite(TRIGGER_PIN, HIGH);
  // ... wait for 11 µs ...
  delayMicroseconds(11);
  // ... put the trigger down ...
  digitalWrite(TRIGGER_PIN, LOW);
  // ... and wait for the echo ...
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}
