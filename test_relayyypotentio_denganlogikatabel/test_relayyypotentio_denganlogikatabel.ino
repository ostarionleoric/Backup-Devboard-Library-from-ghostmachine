float sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue;
int s1 = 9;
int s2 = 8;
int s3 = 7;
int s4 = 6;
int s5 = 5;
int s6 = 4;
int s7 = 3;


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
  int nilaiDayaQ=sensorValue*0.97;
  Serial.print("daya reaktif = ");
  Serial.print(nilaiDayaQ);
  Serial.println(" ");

if(nilaiDayaQ>=1 && nilaiDayaQ<=23){
  digitalWrite(s1, HIGH);
}
else{
  digitalWrite(s1, LOW);
}

if(nilaiDayaQ>=24 && nilaiDayaQ<=37){
  digitalWrite(s2, HIGH);
}
else{
  digitalWrite(s2, LOW);
}


if(nilaiDayaQ>=38&& nilaiDayaQ<=53){

  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
}
else{
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
}


if(nilaiDayaQ>500 && nilaiDayaQ<=600){
  digitalWrite(s4, HIGH);
}
else{
  digitalWrite(s4, LOW);
}

}
