float sensorPin = A0;    // select the input pin for the potentiometer
float sensorValue;
float s1 = 9;
float s2 = 8;
float s3 = 7;
float s4 = 6;
float s5 = 5;
float s6 = 4;
float s7 = 3;


void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(9600);
  pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
      pinMode(s3, OUTPUT);
        pinMode(s4, OUTPUT);
          pinMode(s5, OUTPUT);
            pinMode(s6, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float nilaiDayaQ=sensorValue*0.97;
  Serial.print("daya reaktif = ");
  Serial.print(nilaiDayaQ);
  Serial.println(" ");

if(nilaiDayaQ>=100 && nilaiDayaQ<=200){

  digitalWrite(s1, HIGH);
  
}
else{
  digitalWrite(s1, LOW);
}

if(nilaiDayaQ>=201 && nilaiDayaQ<=300){

  digitalWrite(s2, HIGH);
  
}
else{
  digitalWrite(s2, LOW);
}
if(nilaiDayaQ>300 && nilaiDayaQ<=500){

  digitalWrite(s3, HIGH);
  
}
else{
  digitalWrite(s3, LOW);
}
if(nilaiDayaQ>500 && nilaiDayaQ<=600){

  digitalWrite(s4, HIGH);
  
}
//if(nilaiDayaQ>700 && nilaiDayaQ<=800){

  //digitalWrite(s5, HIGH);
  
//}
//if(nilaiDayaQ>800 && nilaiDayaQ<=900){

  //digitalWrite(s6, HIGH);
  
//}
else{
  //  digitalWrite(s1, LOW);
  //  digitalWrite(s2, LOW);
   // digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
   // digitalWrite(s5, LOW);
    //digitalWrite(s6, LOW);
 }
  //delay(sensorValue);
  // turn the ledPin off:
  //digitalWrite(ledPin, LOW);
  // stop the program for for <sensorValue> milliseconds:
  //delay(sensorValue);
}
