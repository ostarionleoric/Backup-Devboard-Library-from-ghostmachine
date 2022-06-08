#include <MPU6050.h>



//www.nyebarilmu.com

#include <Wire.h>

//#include <LiquidCrystal_PCF8574.h>

//LiquidCrystal_PCF8574 lcd(0x3F); 
// dapat dicek menggunakan i2c finder

MPU6050 mpu;

byte degree[8] = {
  0b00000,
  0b00110,
  0b01111,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};
//<div style="clear:both; margin-top:0em; margin-bottom:1em;"><a href="https://www.nyebarilmu.com/cara-mengakses-motor-servo-menggunakan-arduino/" target="_blank" class="u4cb65d88d81551b3bcd2a450d4d45e90"><!-- INLINE RELATED POSTS 1/1 //--><style> .u4cb65d88d81551b3bcd2a450d4d45e90 { padding:0px; margin: 0; padding-top:1em!important; padding-bottom:1em!important; width:100%; display: block; font-weight:bold; background-color:#ECF0F1; border:0!important; border-left:4px solid #16A085!important; text-decoration:none; } .u4cb65d88d81551b3bcd2a450d4d45e90:active, .u4cb65d88d81551b3bcd2a450d4d45e90:hover { opacity: 1; transition: opacity 250ms; webkit-transition: opacity 250ms; text-decoration:none; } .u4cb65d88d81551b3bcd2a450d4d45e90 { transition: background-color 250ms; webkit-transition: background-color 250ms; opacity: 1; transition: opacity 250ms; webkit-transition: opacity 250ms; } .u4cb65d88d81551b3bcd2a450d4d45e90 .ctaText { font-weight:bold; color:#3498DB; text-decoration:none; font-size: 16px; } .u4cb65d88d81551b3bcd2a450d4d45e90 .postTitle { color:#141414; text-decoration: underline!important; font-size: 16px; } .u4cb65d88d81551b3bcd2a450d4d45e90:hover .postTitle { text-decoration: underline!important; } </style><div style="padding-left:1em; padding-right:1em;"><span class="ctaText">Baca juga :</span>  <span class="postTitle">Cara mengakses Motor Servo menggunakan Arduino</span></div></a></div>
void setup()
{
  Serial.begin(115200);
 
  //lcd.begin(16,2);
  //lcd.createChar(00, degree);
  Serial.begin(9600);
  Serial.println("Initialize MPU6050");
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("tidak ada sensor MPU6050 yang terpasang!");
    delay(500);
  }
 
  //Kalibrasi gyrometer
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
  //lcd.clear();
  //lcd.print("Module MPU6050");
  //lcd.setCursor(00,1);
  //lcd.print("nyebarilmu");
  delay(2000);
  //lcd.clear();
}
 
void loop()
{
  //untuk pembacaan gyrometer
  Vector rawGyro = mpu.readRawGyro();

  Serial.println("Gryometer");
  Serial.print("X : ");
  Serial.print(rawGyro.XAxis);
  Serial.print("Y : ");
  Serial.print(rawGyro.YAxis);
  Serial.print("Z : ");
  Serial.println(rawGyro.ZAxis);

  //lcd.setCursor(00,00);
  //lcd.print(rawGyro.XAxis);
  //lcd.setCursor(5,00);
  //lcd.print(rawGyro.YAxis);
  //lcd.setCursor(10,00);
  //lcd.print(rawGyro.ZAxis);

  //untuk pembacaan accelerometer
  Vector rawAccel = mpu.readRawAccel();

  Serial.println("Accelerometer");
  Serial.print("X : ");
  Serial.print(rawAccel.XAxis);
  Serial.print("Y : ");
  Serial.print(rawAccel.YAxis);
  Serial.print("Z : ");
  Serial.println(rawAccel.ZAxis);

  //lcd.setCursor(00,1);
  //lcd.print(rawAccel.XAxis);
  //lcd.setCursor(5,1);
  //lcd.print(rawAccel.YAxis);
  //lcd.setCursor(10,1);
  //lcd.print(rawAccel.ZAxis);

  float celc = mpu.readTemperature();
 
  Serial.println("temperature ");
  Serial.print(celc);
  Serial.println(" *C");

  //lcd.print("Temperature");
  //lcd.setCursor(13,1);
  //lcd.print(celc);
  //lcd.write((byte)00);
 
  delay(500);
}
