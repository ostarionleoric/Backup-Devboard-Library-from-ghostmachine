int Gas_analog = 35;
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "realme";   // your network SSID (name) 
const char* password = "samasama";   // your network password

WiFiClient  client;
unsigned long myChannelNumber = 1559606;
const char * myWriteAPIKey = "9EFBYJNGWEASLPGT";
//unsigned long lastTime = 0;
//unsigned long timerDelay = 300;

void setup() {
pinMode(Gas_analog, INPUT);
Serial.begin(9600);
WiFi.mode(WIFI_STA);   
ThingSpeak.begin(client);

WiFi.begin(ssid, password); 

}

void loop() {
  // put your main code here, to run repeatedly:
   int gassensorAnalog = analogRead(Gas_analog);

  Serial.print("CO : ");
  Serial.println(gassensorAnalog);


  Serial.print("Carbon : ");
  Serial.println(gassensorAnalog);

  //ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  //ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, gassensorAnalog, myWriteAPIKey);
 // ThingSpeak.writeField(myChannelNumber, 5, codua, myWriteAPIKey);
  




   

}
