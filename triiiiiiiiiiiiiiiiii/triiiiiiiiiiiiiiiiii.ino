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
delay(50);
sensorValue = analogRead(A0);

if (sensorValue>sensorValue1 && sensorValue>512){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue==510 || sensorValue==511 || sensorValue==512 || sensorValue==513 ){
Serial.println("0  volt");
  }  
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-220)+240;
  Serial.print(Veff);
  Serial.print("  volt");
  Serial.println(sensorValue);
 // Serial.println(VmaxD);
  
  //VmaxD=0;
  
}
}
