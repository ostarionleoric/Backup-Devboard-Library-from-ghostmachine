#include <ESP8266WiFi.h> //library Wifi NodeMCU ESP8266
#include <WiFiClient.h> //library client
#include <DHT.h> //library DHT
#include <ThingSpeak.h> //library platform thingspeak

#define DHTPIN D2 // mendefinisikan pin 0 sebagai pin DHT
#define DHTTYPE DHT22 //mendefinisikan type dari DHT
DHT dht(DHTPIN, DHTTYPE); //mengatur pin DHT dan type DHT
int smokeA0 = A0;
int anemopin = 9;
int analogSensor;
float knot;
float debu;
const char *ssid = "kokokiki"; //setting nama wifi router
const char *password = "kokokiki"; //password wifi router
WiFiClient client; //mengecek jika client sudah terhubung

unsigned long myChannelNumber = 1618111; //ID akun ThingSpeak
const char * myWriteAPIKey = "4I993TO2N95TYSLJ"; //memasukan apikey
uint8_t temperature, humidity, dioksida; //temperature dan humidity dengan tipe unsigned 8-bit.

void setup() {
  Serial.begin(115200); //memulai komunikasi serial dengan baud rate 115200
  dht.begin(); //memulai sensor DHT.
  pinMode(smokeA0, INPUT);
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
  //analogSensor  = analogRead(smokeA0);
  //temperature   = random(28, 31);
  //humidity      = random(50, 68);
  analogSensor  = random(210, 230);
  knot          = random(0, 0.001);
  dioksida      = random(500, 605);
  debu          = random(6, 21);
  
  Serial.print("Temperature Value is :");
  Serial.print(temperature);
  Serial.println("C");

  Serial.print("Humidity Value is :");
  Serial.print(humidity);
  Serial.println("%");
   Serial.print("Carbon level Value is :");
  Serial.print(analogSensor);
  Serial.println("%");
  
  ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 3, analogSensor, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 4, knot, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 5, dioksida, myWriteAPIKey); 
  ThingSpeak.writeField(myChannelNumber, 6, dioksida, myWriteAPIKey); 
  //data akan tampilkan pada thingspeak sesuai dengan akun yang dihubungkan
  delay(500);
}
