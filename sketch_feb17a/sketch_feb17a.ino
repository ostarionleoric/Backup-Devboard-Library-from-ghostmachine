const unsigned int numReadings=200;
int readingsVClamp[numReadings]; // samples of the sensor SCT-013-000
int readingsGND[numReadings]; // samples of the <span id="result_box" class="" lang="en"><span class="hps">virtual</span> <span class="hps alt-edited">ground</span></span>
float SumSqGND = 0; 
float SumSqVClamp = 0;
float total = 0; 


int PinVClamp = A0; // Sensor SCT-013-000
int PinVirtGND = A1; // <span id="result_box" class="" lang="en"><span class="hps">Virtual</span> <span class="hps alt-edited">ground</span></span>

void setup() {
Serial.begin(9600);
for (int thisReading = 0; thisReading < numReadings; thisReading++) {
readingsVClamp[thisReading] = 0;
readingsGND[thisReading] = 0;
}
}
void loop() {
unsigned int i=0;
SumSqGND = 0;
SumSqVClamp = 0;
total = 0;
for (unsigned int i=0; i<numReadings; i++)
{
readingsVClamp[i] = analogRead(PinVClamp) - analogRead(PinVirtGND);
delay(1); // 
}
for (unsigned int i=0; i<numReadings; i++)
{
SumSqVClamp = SumSqVClamp + sq((float)readingsVClamp[i]);
}
total = sqrt(SumSqVClamp/numReadings);
total= (total*(float)2/3);
Serial.println(total);
delay(1500); 
}
