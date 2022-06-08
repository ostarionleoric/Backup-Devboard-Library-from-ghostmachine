/**
 * Program untuk membaca suhu dan kelembaban dari sensor DHT22
 * menggunakan NodeMCU
 *
 * Hak cipta (c) 2016 x.benny.id. All rights reserved.
 * https://x.benny.id
 */

// Konfigurasi DHT22
#include <DHT.h>
#define DHTPIN D2          // PIN D3 (GPIO 0) dari NodeMCU terhubung dengan PIN Data dari DHT22
#define DHTTYPE DHT22     // Kita menggunakan tipe DHT22
DHT dht(DHTPIN, DHTTYPE); // Inisialisasi DHT22

// Konfigurasi WiFi
#include <ESP8266WiFi.h>
#define WIFI_SSID "Kokokiki"                   // Ganti dengan SSID WiFi yang digunakan
#define WIFI_PASS "kokokiki"             // Ganti dengan password WiFi yang benar

// Konfigurasi ThingSpeak
#include <PubSubClient.h>
#define THINGSPEAK_CLIENT_ID "1559606"      // Bisa diganti dengan Client ID Sembarang
#define THINGSPEAK_MQTT_API "SomeMQTTAPIKey"  // Ganti dengan User MQTT API Key dari ThingSpeak
#define THINGSPEAK_CHANNEL_API "9EFBYJNGWEASLPGT"     // Ganti dengan Channel API Key dari ThingSpeak
#define THINGSPEAK_CHANNEL_ID 1559606           // Ganti dengan Channel ID dari ThingSpeak

// Mempersiapkan NodeMCU melalui fungsi setup()
// Catatan: Nama fungsi dibawah ini tidak boleh dirubah
void setup() {
  // Inisialisasi Serial port untuk debugging
  Serial.begin(115600);
  Serial.setTimeout(2000);
  while(!Serial) { }
  Serial.println("NodeMCU Siap Dipakai");

  // Mengaktifkan koneksi WiFi
  Serial.print("Menhubungkan dengan WiFi: ");
  Serial.println(WIFI_SSID);
  int wifiStatus = startWiFi(WIFI_SSID, WIFI_PASS);
  
  Serial.println("Membaca sensor DHT22");
}

int timeSinceLastRead = 0;
void loop() {

  // Report every 10 seconds.
  if(timeSinceLastRead > (10000)) {
    // Membaca kelembaban
    float h = dht.readHumidity();
    // Membaca suhu dalam derajat celcius
    float t = dht.readTemperature();
    // Membaca suhu dalam derajat farenheit
    float f = dht.readTemperature(true);

    // Memastikan kalau semua pembacaan sukses
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    // Menghitung index suhu dalam farenheit
    float hif = dht.computeHeatIndex(f, h);
    // Menghitung index suhu dalam farenheit
    float hic = dht.computeHeatIndex(t, h, false);

    // Menulis hasil pembacaan melalui Serial
    Serial.print("\Kelembaban: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Suhu: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t");
    Serial.print("Persepsi Suhu: ");
    Serial.print(hic);
    Serial.print(" *C ");
    Serial.print(hif);
    Serial.println(" *F");

    timeSinceLastRead = 0;
    int mqttThingSpeakResult = sendThingSpeak(t, h); // Di kita mengirimkan data ke ThingSpeak
  }
  delay(1000); // Menunggu pembacaan selanjutnya
  timeSinceLastRead += 1000;
}
