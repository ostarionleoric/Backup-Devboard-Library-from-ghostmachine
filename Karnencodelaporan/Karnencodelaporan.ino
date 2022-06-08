#include <ESP8266WiFi.h> //library Wifi NodeMCU ESP8266
#include <WiFiClient.h> //library client
#include <DHT.h> //library DHT
#include <ThingSpeak.h> //library platform thingspeak

#define DHTPIN D7 // mendefinisikan pin 7 sebagai pin DHT
#define DHTTYPE DHT22 //mendefinisikan type dari DHT
DHT dht(DHTPIN, DHTTYPE); //mengatur pin DHT dan type DHT
int sensorValue = 0;
float sensorVoltage = 0;
float windSpeed = 0;
float voltageConversionConstant = .004882814;
int sensorDelay = 1000;
float voltageMin = .4;
float windSpeedMin = 0;
float voltageMax = 2.0;
float windSpeedMax = 32;
int coA2 = A0;
int pinco2=A1;

int anemopin=9;
int pindebu=A1;
int co;

int ledPower = 2;
int measurePin = A2;
int samplingTime = 280;
int sleepTime = 100;
 
float voMeasured = 0;
float calcVoltage = 0;
float debu = 0;
float voltDensity = 0;
float knot;

const char *ssid = "kokokiki"; //setting nama wifi router
const char *password = "kokokiki"; //password wifi router
WiFiClient client; //mengecek jika client sudah terhubung

unsigned long myChannelNumber = 1618111; //ID akun ThingSpeak
const char * myWriteAPIKey = "4I993TO2N95TYSLJ"; //memasukan apikey
uint8_t temperature, humidity, dioksida; //temperature dan humidity dengan tipe unsigned 8-bit.

void setup() {
  Serial.begin(115200); //memulai komunikasi serial dengan baud rate 115200
  dht.begin(); //memulai sensor DHT.
  pinMode(coA2, INPUT);
  pinMode(anemopin, INPUT);
  pinMode(ledPower,OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //menghubungkan dengan wifi router
  while (WiFi.status() != WL_CONNECTED) //Cek koneksi Wifi.
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client); //melakukan inisialisasi ke thingspeak
}

void loop()
{
  temperature = dht.readTemperature(); //membaca suhu pada sensor DHT11
  humidity = dht.readHumidity(); //membaca kelembaban sensor DHT11
  co  = analogRead(coA2)/100;
  
  dioksida      = analogRead(pinco2);
   digitalWrite(ledPower,LOW); // power on the LED
      delayMicroseconds(samplingTime);
     
      voMeasured = analogRead(measurePin); // read the dust value
      digitalWrite(ledPower,HIGH); // turn the LED off
      delayMicroseconds(sleepTime);
     
      calcVoltage = ( ( voMeasured * 5 ) / 1024);
      voltDensity = calcVoltage - 0.6;
      debu = voltDensity * 0.17;
     sensorValue = digitalRead(anemopin);
    sensorVoltage = sensorValue * voltageConversionConstant;
if (sensorVoltage <= voltageMin) { 
    knot = 0; 
}
else { 
    knot = (sensorVoltage - voltageMin)*windSpeedMax/(voltageMax - voltageMin); 
}
  Serial.print("Temperature Value is :");
  Serial.print(temperature);
  Serial.println("C");

  Serial.print("Humidity Value is :");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Carbon mono level Value is :");
  Serial.print(co);
  Serial.println("%");
  
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 3, co, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 4, knot, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 5, dioksida, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 6, debu, myWriteAPIKey); 
  //data akan tampilkan pada thingspeak sesuai dengan akun yang dihubungkan
  delay(500);
}
