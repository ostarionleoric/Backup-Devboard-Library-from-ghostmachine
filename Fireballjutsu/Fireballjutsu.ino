#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>  
#include "DHT.h"

 
#define FIREBASE_HOST "pencemaran-udara-default-rtdb.firebaseio.com"      
#define FIREBASE_AUTH "6Nvv5UIpV8hPdMYX60zK9AW296rckOdaXyxT52fp"            
#define WIFI_SSID "Redmi Note 4"                                  
#define WIFI_PASSWORD "nigeltonberi"            
 
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTPin D2                                      // Initialize dht type as DHT 11

DHT dht(DHTPin, DHTTYPE);                                                        
 
void setup() 
{
  Serial.begin(115200);
  dht.begin();                                                  //reads dht sensor data 
               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                  
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.print("Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                               //prints local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                 // connect to the firebase
 
}
 
void loop() 
{
  float h = dht.readHumidity();                                 // Read Humidity
  float t = dht.readTemperature();                              // Read temperature
  
  if (isnan(h) || isnan(t))                                     // Checking sensor working
  {                                   
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 
  Serial.print("Humidity: ");  
  Serial.print(h);
  String fireHumid = String(h) + String("%");                   //Humidity integer to string conversion
  
  Serial.print("%  Temperature: ");  
  Serial.print(t);  
  Serial.println("°C ");
  String fireTemp = String(t) + String("°C");                  //Temperature integer to string conversion
  delay(5000);
 
 
  Firebase.pushString("/DHT11/Humidity", fireHumid);            //setup path to send Humidity readings
  Firebase.pushString("/DHT11/Temperature", fireTemp);         //setup path to send Temperature readings
    if (Firebase.failed()) 
    {
 
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error()); 
      return;
  }
}
