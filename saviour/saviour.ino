#include <WiFi.h>
#include <Ultrasonic.h>
#include "HX711.h"

Ultrasonic ultrasonic(5, 18);

int distance;
#define DOUT  25
#define CLK  27
HX711 scale(DOUT, CLK);

float calibration_factor = 219.90;
int GRAM;


const char* ssid = "ROG_Phone3_2569";
const char* password = "11111111";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
const char* statu = "Abnormal";
void setup() {
  Serial.begin(115200);
 scale.set_scale();
  scale.tare();
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();
  scale.set_scale(calibration_factor);
   GRAM = scale.get_units(), 4;
if(GRAM > 2000){
  statu = "normal";
}
else{
  statu = "abnormal";
}
   
  if (client) {                            
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" http-equiv=\"refresh\" content=\"5\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the table 
            client.println("<style>body { text-align: ; font-family: \"Trebuchet MS\", Arial;}");
            client.println("table { border-collapse: collapse; width:35%; margin-left:auto; margin-right:auto; }");
            client.println("th { padding: 12px; background-color: #0043af; color: white; }");
            client.println("tr { border: 1px solid #ddd; padding: 12px; }");
            client.println("tr:hover { background-color: #bcbcbc; }");
            client.println("td { border: none; padding: 12px; }");
            client.println(".sensor { color:white; font-weight: bold; background-color: #bcbcbc; padding: 1px; }");
            
            // Web Page Heading
            client.println("</style></head><body><center><h1>Alat ukur posyandu</h1></center>");
            //client.println("<table><tr><th>MEASUREMENT</th><th>VALUE</th></tr>");
            client.println("<table><tr></tr>");
            client.println("<tr><td>No ID</td><td><span class=\"\">");
            client.println("001");
            client.println("</span></td></tr>"); 
            client.println("<tr><td>Nama</td><td><span class=\"\">");
            client.println("muhajir");
            client.println("</span></td></tr>"); 
            client.println("<tr><td>Umur</td><td><span class=\"\">");
            client.println("6");
            client.println("</span></td></tr>"); 
            client.println("<tr><td>Panjang </td><td><span class=\"sensor\">");
            client.println(ultrasonic.read());
            client.println(" CM</span></td></tr>"); 
            client.println("<tr><td>Berat </td><td><span class=\"sensor\">");
            client.println(GRAM);
            client.println(" Gram</span></td></tr>"); 
            client.println("<tr><td>Status</td><td><span class=\"\">");
            client.println(statu);
            client.println("</span></td></tr>"); 
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
