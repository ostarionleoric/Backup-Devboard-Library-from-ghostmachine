
const int sensorpin = 2;                      
const unsigned long sampleTime = 2560; 


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float rpm = getRPM(); 
Serial.println(rpm);
}
float getRPM() 
{ 
 float count = 0; 
 boolean countFlag = LOW; 
 float currentTime = 0; 
 float startTime = millis(); 
 while (currentTime <= sampleTime) 
 { 
   if (digitalRead(sensorpin) == HIGH) 
   { 
     countFlag = HIGH; 
   } 
   if (digitalRead(sensorpin) == LOW && countFlag == HIGH) 
   { 
     count++; 
     countFlag=LOW; 
   } 
   currentTime = millis() - startTime; 
 } 
 float countRpm = float(60000/float(sampleTime))*count; 
 return countRpm; 
} 
