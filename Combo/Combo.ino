#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <WiFiUdp.h>

const char* ssid = "Ruang Kerja Gubernur";
const char* password = "12345678";

#define DHTTYPE DHT11   // DHT 11
 
int LED1 = D2; //D7 on ESP Board
int LED2 = D3; //D6 on ESP Board
int LED3 = D4; //D5 on ESP Board
int LED4 = D5;  //D4 on ESP Board
  int value1 = LOW;
  int value2 = LOW;
  int value3 = LOW;
  int value4 = LOW;
  
WiFiServer server(80);

uint8_t DHTPin = D7;
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity; 
 float Temperaturestat;
 float Humiditystat;
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

    dht.begin(); 
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
          
// Set LED according to the request
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  
 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
  client.println("<title>TA Misbah</title>\n");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n");
  client.println("body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n");

//untuk atur tampilan button
  client.println(".button {display: block;width: 120px;background-color: #1abc9c;border: none;color: white;padding: 13px 13px;text-decoration: none;font-size: 25px;margin: 0px auto 2px;cursor: pointer;border-radius: 4px;}\n");
  client.println(".button-on {background-color: #1abc9c;}\n");
  client.println(".button-on:active {background-color: #16a085;}\n");
  client.println(".button-off {background-color: #34495e;}\n");
  client.println(".button-off:active {background-color: #2c3e50;}\n");

  client.println("p {font-size: 14px;color: #888;margin-bottom: 10px;}");

  //client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");         

client.println(".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n");
client.println(".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n");
client.println(".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n");
client.println(".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n");
client.println(".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n");
client.println(".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n");
client.println(".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n");
client.println(".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n");
client.println(".data{padding: 10px;}\n");

client.println("</style>\n");
  //Javascript untuk menampilkan pembacaan sensor dinamis
client.println("<script>\n");
client.println("setInterval(loadDoc,200);\n");
client.println("function loadDoc() {\n");
client.println("var xhttp = new XMLHttpRequest();\n");
client.println("xhttp.onreadystatechange = function() {\n");
client.println("if (this.readyState == 4 && this.status == 200) {\n");
client.println("document.getElementById(\"webpage\").innerHTML =this.responseText}\n");
client.println("};\n");
client.println("xhttp.open(\"GET\", \"/\", true);\n");
client.println("xhttp.send();\n");
client.println("}\n");
client.println("</script>\n");
//--------------- 

client.println("<div id=\"webpage\">\n");
client.println("<h1>TA Misbah Sulaiman Nura</h1>\n");
client.println("<div class=\"data\">\n");

//tampilan icon suhu
client.println("<div class=\"side-by-side temperature-icon\">\n");
client.println("<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n");
client.println("width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n");
client.println("<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n");
client.println("c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n");
client.println("c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n");
client.println("c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n");
client.println("c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n");
client.println("</svg>\n");
client.println("</div>\n");
//-------------

//tampilan tulisan suhu
client.println("<div class=\"side-by-side temperature-text\">Suhu :</div>\n");
client.println("<div class=\"side-by-side temperature\">");
client.println((int)Temperature);
client.println("<span class=\"superscript\">°C</span></div>\n");
client.println("</div>\n");
//--------------


//tampilan ikon humidity
client.println("<div class=\"data\">\n");
client.println("<div class=\"side-by-side humidity-icon\">\n");
client.println("<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n");
client.println("<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n");
client.println("c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n");
client.println("</svg>\n");
client.println("</div>\n");
//----------------

//tampilan humidity
/*client.println("<div class=\"side-by-side temperature-text\">Kelembapan :</div>\n");
client.println("<div class=\"side-by-side temperature\">";
client.println((int)Humiditystat;
client.println("<span class=\"superscript\">%</span></div>\n");
client.println("</div>\n");*/

client.println("<div class=\"side-by-side humidity-text\">Kelembapan :</div>\n");
client.println("<div class=\"side-by-side humidity\">");
client.println((int)Humidity);
client.println("<span class=\"superscript\">%</span></div>\n");
client.println("</div>\n");

//pemisah  
  client.println("<br><br>");
  client.println("<fieldset>");
  client.println("<font color = #000000>");
  client.print("Controlling Perangkat:");
  client.println("</font>");
  client.println("</fieldset>");
  client.println("<br><br>");
 
 // Return the response LED1
  client.print("LED1 is now: ");
  // Control LED 1
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(LED1, HIGH);
    value1 = HIGH;
    }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(LED1, LOW);
    value1 = LOW;
     } 
        if(value1==HIGH){client.print("ON");
     client.println("<br><br>");
    client.println("<a href=\"/LED1=OFF\"\"><button class=\"button button-off\">OFF</button></a>\n");}
     if(value1==LOW){client.print("OFF");
     client.println("<br><br>");
      client.println("<a href=\"/LED1=ON\"\"><button class=\"button button-on\">ON</button></a>\n");}

  

 // Return the response LED2
 client.println("<br><br>");
 client.print("LED2 is now: ");
  // Control LED 2
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(LED2, HIGH);
    value2 = HIGH;
    }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(LED2, LOW);
    value2 = LOW;
    }
        if(value2==HIGH){client.print("ON");
     client.println("<br><br>");
    client.println("<a href=\"/LED2=OFF\"\"><button class=\"button button-off\">OFF</button></a>");}
     if(value2==LOW){client.print("OFF");
     client.println("<br><br>");
      client.println("<a href=\"/LED2=ON\"\"><button class=\"button button-on\">ON</button></a>");}
 
  // Return the response LED3
  client.println("<br><br>");
  client.print("LED3 is now: ");
  // Control LED 3
  if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(LED3, HIGH);
    value3 = HIGH;
    }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(LED3, LOW);
    value3 = LOW;
    }
      if(value3==HIGH){client.print("ON");
     client.println("<br><br>");
    client.println("<a href=\"/LED3=OFF\"\"><button class=\"button button-off\">OFF</button></a>\n");}
     if(value3==LOW){client.print("OFF");
     client.println("<br><br>");
      client.println("<a href=\"/LED3=ON\"\"><button class=\"button button-on\">ON</button></a>\n");}

 
  // Return the response LED4
  client.println("<br><br>");
  client.print("LED4 is now: ");
  // Control LED 4
  if (request.indexOf("/LED4=ON") != -1)  {
    digitalWrite(LED4, HIGH);
    value4 = HIGH;
    } 
  if (request.indexOf("/LED4=OFF") != -1)  {
    digitalWrite(LED4, LOW);
    value4 = LOW;
    }
    if(value4==HIGH){client.print("ON");
     client.println("<br><br>");
    client.println("<a href=\"/LED4=OFF\"\"><button class=\"button button-off\">OFF</button></a>\n");}
     if(value4==LOW){client.print("OFF");
     client.println("<br><br>");
      client.println("<a href=\"/LED4=ON\"\"><button class=\"button button-on\">ON</button></a>\n");}
     
 
 
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
