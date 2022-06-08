#include <WiFi.h>
#include "ThingSpeak.h"
const char* ssid = "realme";   // your network SSID (name) 
const char* password = "samasama";   // your network password
WiFiClient  client;
unsigned long myChannelNumber = 1559606;
const char * myWriteAPIKey = "9EFBYJNGWEASLPGT";
int smokeA0 = 35;

// Your threshold value. You might need to change it.
int sensorThres = 600;

void setup() {
 //pinMode(buzzer, OUTPUT);
 pinMode(smokeA0, INPUT);
 Serial.begin(9600);
 WiFi.mode(WIFI_STA);   
ThingSpeak.begin(client);
WiFi.begin(ssid, password); 
}

void loop() {
 int analogSensor = analogRead(smokeA0);
//int sensorThres = 22;
 Serial.print("Pin A0: ");
 Serial.println(analogSensor);
  ThingSpeak.writeField(myChannelNumber, 3, analogSensor, myWriteAPIKey);
 // Checks if it has reached the threshold value
/** if (analogSensor > sensorThres)
 {
   tone(buzzer, 1000, 200);
 }
 else
 {
   noTone(buzzer);
 }
 delay(100);
 **/
}
