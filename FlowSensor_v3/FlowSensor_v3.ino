#define buzzer 12

byte indikator = 13;

byte sensorInt = 0;
byte flowsensor = 2;

float konstanta = 8.5; //konstanta flow meter
float harga = 2800;
float hargatotal;
volatile byte pulseCount;

float debit;
float flowmlt;
float totalmlt;

unsigned long oldTime;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{

  // Inisialisasi port serial
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(indikator, OUTPUT);
  digitalWrite(indikator, HIGH);
  pinMode(buzzer, OUTPUT);
  digitalWrite (buzzer, LOW);

  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH);

  pulseCount = 0;
  debit = 0.0;
  flowmlt = 0;
  totalmlt = 0;
  oldTime = 0;

  attachInterrupt(sensorInt, pulseCounter, FALLING);
}


void loop()
{

  if ((millis() - oldTime) > 1000)
  {
  

    if (hargatotal >= 60) {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
          
    }

    else if (hargatotal > 50) {
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }

    else if (hargatotal <= 50) {
      digitalWrite (buzzer, LOW);
    }
     detachInterrupt(sensorInt);
    debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
    oldTime = millis();
    flowmlt = (debit / 60) * 1000;
    totalmlt += flowmlt;
    hargatotal = totalmlt * harga * 0.000001; 

    unsigned int frac;

    Serial.print("Debit air: ");
    Serial.print(int(debit));
    Serial.print("L/min");
    Serial.print("\t");

    Serial.print("Volume: ");
    Serial.print(totalmlt);
    Serial.print("mL");
    Serial.print("\t");

    Serial.print("RP: ");
    Serial.print(hargatotal);
    Serial.println(" ");


    lcd.setCursor(0, 0);
    lcd.print("V air =");
    lcd.setCursor(8, 0);
    lcd.print (totalmlt / 1000, 3);
    lcd.setCursor(15, 0);
    lcd.print("Liter");
    lcd.setCursor(0, 1);
    lcd.print("Rp:");
    lcd.setCursor(4, 1);
    
    lcd.print(hargatotal);
    lcd.setCursor(0, 1);
    pulseCount = 0;

    attachInterrupt(sensorInt, pulseCounter, FALLING);
  }
}


void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
