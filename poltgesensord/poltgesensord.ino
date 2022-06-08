double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;
void setup() {
Serial.begin(9600);
}
void loop() {
sensorValue1=sensorValue;
delay(2);
sensorValue = analogRead(A0);
float kambing = (sensorValue / 1023.0)*5.0;
if (sensorValue>sensorValue1 && sensorValue>513){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-220)+240;
  Serial.println(Veff); 
  //Serial.println(analogRead(A0));
 // Serial.println(kambing);
  
  VmaxD=0;
}
}
