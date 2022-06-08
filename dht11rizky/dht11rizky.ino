#include "DHT.h"

   
#define DHTTYPE DHT11   
#define DHTPIN 25  
DHT dht(DHTPIN, DHTTYPE);

int UVOUT = 36; //Output from the sensor
int REF_3V3 = 39; //3.3V power on the Arduino board
 

void setup() {
  Serial.begin(9600);
  Serial.println("Deteksi Suhu dan kelembaban");
  dht.begin();
    pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
}

void loop() {
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);
  
  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;
  
  float uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level
 
  Serial.print("output: ");
  Serial.println(refLevel);
 
  Serial.print("ML8511 output: ");
  Serial.println(uvLevel);
 
  //Serial.print(" / ML8511 voltage: ");
  //Serial.println(outputVoltage);
 
  Serial.print(" / UV Intensity (mW/cm^2): ");
  Serial.println(uvIntensity);
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(h) || isnan(t)) {
    Serial.println("Semsor tidak terbaca!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
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
