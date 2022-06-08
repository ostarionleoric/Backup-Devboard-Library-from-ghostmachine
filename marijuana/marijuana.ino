unsigned long time;
int pin = 13;
unsigned long duration;
void setup() {
  Serial.begin(9600);
   pinMode(pin, INPUT_PULLUP);
}
void loop() {
  //int sensorVal = digitalRead(2);
duration = pulseIn(pin, HIGH);
Serial.print("baca selama ");
  Serial.println(duration);
 // Serial.println(sensorVal);
 //if (sensorVal == HIGH) {
//    digitalWrite(13, LOW);
  //Serial.print("Time: ");
  //time = micros();

  //Serial.println(time); //prints time since program started
            // wait a second so as not to send massive amounts of data

  //} else {
    //digitalWrite(13, HIGH);
    //Serial.println("stop ");
    
  //}
}
