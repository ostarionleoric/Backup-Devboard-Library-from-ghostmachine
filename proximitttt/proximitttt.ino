int sensorState = 0;

void setup() {
  // pinMode(3, INPUT);
   pinMode(13, OUTPUT);
   Serial.begin(9600);
}

void loop() {
   sensorState = analogRead(A0);

   if (sensorState == LOW) {
     digitalWrite(13, LOW);
        }
   else {
      digitalWrite(13, HIGH);
   }
   
   Serial.println(sensorState);
}
