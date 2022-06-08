/*
  Adapted from WriteSingleField Example from ThingSpeak Library (Mathworks)
  
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-thingspeak-publish-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/
#include "DHT.h"
#define DHTTYPE DHT11   
#define DHTPIN 25  
DHT dht(DHTPIN, DHTTYPE);
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int UVOUT = 36; //Output from the sensor
int REF_3V3 = 39; //3.3V power on the Arduino board
 

#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "realme";   // your network SSID (name) 
const char* password = "samasama";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1614844;
const char * myWriteAPIKey = "HVXXIFWGUDCZ0Z2Q";

//unsigned long myChannelNumber = 1614842;
//const char * myWriteAPIKey = "OU73FSG000S5D7A2";



// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
uint8_t t, h; //temperature dan humidity dengan tipe unsigned 8-bit.

float uvIntensity;

// Variable to hold temperature readings
//float temperatureC;
//uncomment if you want to get temperature in Fahrenheit
//float temperatureF;

// Create a sensor object
//Adafruit_BME280 bme; //BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)

void setup() {
  Serial.begin(115200);  //Initialize serial
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  dht.begin();
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
   //Convert the voltage to a UV intensity level
 t = dht.readTemperature();
   h = dht.readHumidity();
   uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(3000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
      t = dht.readTemperature();
      h = dht.readHumidity();
      uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0);
    Serial.print("Temperature (ºC): ");
    Serial.println(t);
    Serial.print("humid (ºC): ");
    Serial.println(h);
    Serial.print("UV intensity: ");
    Serial.println(uvIntensity);
    
    //uncomment if you want to get temperature in Fahrenheit
    /*temperatureF = 1.8 * bme.readTemperature() + 32;
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureF);*/
    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    //int x = ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
    //int y = ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
    //ThingSpeak.writeField(myChannelNumber, 3, uvIntensity, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    //if(x == 200 && y == 200){
    //  Serial.println("Channel update successful.");
   // }

   // else{
   //   Serial.println("Problem updating channel. HTTP error code " + String(x) + String(y));
   // }
    lastTime = millis();
  }
  
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, uvIntensity, myWriteAPIKey);
    lcd.setCursor(0,0);
  lcd.print("     DATA LOGGER");
  lcd.setCursor(0,1);
  lcd.print("Suhu       = ");
  lcd.print(t);
  lcd.setCursor(0,2);
  lcd.print("Kelembaban = ");
  lcd.print(h);
  lcd.setCursor(0,3);
  lcd.print("UV         = ");
  lcd.print(uvIntensity);
  delay(1000);
  lcd.clear();
  //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");
}
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 
 
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;
 
  return(runningValue);
}
 
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
