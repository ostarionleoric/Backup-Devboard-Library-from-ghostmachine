#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#include "HX711.h"

#define TRIGGER_PIN 3
#define ECHO_PIN 5
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250

#define DOUT  A0
#define CLK  A1
#define DOUT2  A2
#define CLK2  A3

int sensorValue;

int sensorValue2;

HX711 scale(DOUT, CLK);
HX711 scale2(DOUT2, CLK2);
float calibration_factor = 219.90;
int GRAM;
int GRAM2;
float abso;

void setup() {
  Serial.begin(9600);
  scale.set_scale();
  scale.tare();
  scale2.set_scale();
  scale2.tare();
     pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(500);
   lcd.init();             
  lcd.backlight();

}

void loop() {
  lcd.clear();
  sensorValue2 = analogRead(A1);
  sensorValue = analogRead(A0);
   // delay(MEASURE_DELAY);
  int distance = measure();
  scale.set_scale(calibration_factor);
  scale2.set_scale(calibration_factor);
  GRAM = scale.get_units(), 4;
  GRAM2 = scale2.get_units(), 4;
  Serial.print("timbagan satu :");
  Serial.println(GRAM);
  //delay(500);
  Serial.print("timbagan dua :");
  Serial.println(GRAM2);
  //delay(500);
  Serial.print("TOTAL BERAT :");
  Serial.println(GRAM+GRAM2);
    Serial.print("nilai analog BERAT :");
  Serial.println(sensorValue);
  Serial.println(sensorValue2);
  Serial.print("TOTAL PANJANG :");
  Serial.println(120-(distance*0.1));
  lcd.setCursor(0,0);
  lcd.print("TINGGI");
  lcd.setCursor(7,0);
  lcd.print(120-(distance*0.1));
    lcd.setCursor(14,0);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print("BERAT");
  lcd.setCursor(7,1);
  abso = abs((GRAM+GRAM2)*0.001);
  //lcd.print((GRAM+GRAM2)*0.001);
   lcd.print(abso);
  lcd.setCursor(14,1);
  lcd.print("kg");
  delay(2500);
  
  
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
