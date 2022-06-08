
#include "DHT.h"

#define DHTPIN 5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
int Gas_analog = 35;
int debu = random(6, 23);
DHT dht(DHTPIN, DHTTYPE);

#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "realme";   // your network SSID (name) 
const char* password = "samasama";   // your network password

WiFiClient  client;

//unsigned long myChannelNumber = 1559606;
//const char * myWriteAPIKey = "9EFBYJNGWEASLPGT";


unsigned long myChannelNumber = 1618111;
const char * myWriteAPIKey = "4I993TO2N95TYSLJ";



unsigned long lastTime = 0;
unsigned long timerDelay = 300;

void setup() {
  Serial.begin(115200);

pinMode(Gas_analog, INPUT);
  dht.begin();
    WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);
}

void loop() {
 

  int gassensorAnalog = analogRead(Gas_analog);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int codua = random(200, 260);
  debu = random(6, 23);
  //gassensorAnalog - 3;
  
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


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

      t = dht.readTemperature();
      h = dht.readHumidity();
      gassensorAnalog = analogRead(Gas_analog);
      //codua = gassensorAnalog - 3;
      
  Serial.print("CO : ");
  Serial.println(gassensorAnalog);
  Serial.print("CO2: ");
  Serial.println(codua);
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));

    lastTime = millis();
  }
  
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3, gassensorAnalog, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4, debu, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5, codua, myWriteAPIKey);
  
  /**Serial.print("CO: ");
  Serial.println(gassensorAnalog);
  Serial.print("CO2: ");
  Serial.println(gassensorAnalog-3);
  
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  **/
}
