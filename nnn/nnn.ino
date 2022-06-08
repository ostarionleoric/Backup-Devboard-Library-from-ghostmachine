/* Membuat WiFi access point dan layanan sebuah web server dengan  Arduino "Wemos". */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Membuat nama ssid dan password wifi-nya atau hostpot */
const char *ssid = "JARVIS"; /* dengan type data konstanta */
const char *password = "krnu5860";

ESP8266WebServer server(80); /* Port 80

/* Untuk mengirimkan sebuah pesan.  Coba ketik di Url anda dengan http://192.168.4.1 di web browser anda
 * Sebelum anda masukan Ip Address tersebut, di harapkan anda koneksi dulu dengan nam AP-nya.
 */
void handleRoot() {
 server.send(200, "text/html", "<center><h1>JARVIS DISINI</h1></center>"); /* menggunakan tabahan bahasa HTML (WEB) */
 
 
}

void setup() {
 delay(1000);
 Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println();
 Serial.print("Configuring access point...");
 /* Kamu bisa menghapus parameter jika kamu. */
 WiFi.softAP(ssid, password);

 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
 server.on("/", handleRoot);
 server.begin();
 Serial.println("HTTP server started");
 Serial.write(Serial.read());
}

void loop() {
 server.handleClient();
 Serial.println(Serial.read());
}
