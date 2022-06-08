
const int hallSensorPin = 2;                      // connect the hall effect sensor on pin 2
const unsigned long sampleTime = 1000;
const int maxRPM = 1260;                  // maximum RPM for LCD Bar
int rpmMaximum = 0;

void setup() 
{
  pinMode(hallSensorPin,INPUT);
  Serial.begin(9600);
  delay(1000);
}

void loop() 
{
  delay(100);
  int rpm = getRPM();
  if (rpm > rpmMaximum) rpmMaximum = rpm;
  
  displayRPM(rpm);
  displayBar(rpm);
  
}
 
int getRPM()
{
  int count = 0;
  boolean countFlag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    if (digitalRead(hallSensorPin) == HIGH)
    {
      countFlag = HIGH;
    }
    if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH)
    {
      count++;
      countFlag=LOW;
    }
    currentTime = millis() - startTime;
  }
  int countRpm = int(60000/float(sampleTime))*count;
  return countRpm;
}
    
void displayRPM(int rpm) 
{

float rumus= 2*3.14*4;
float detik=60;

  Serial.print("RPM = ");
  Serial.print(rpm);
  Serial.print("  KM/S = ");
  Serial.print(rpm*(rumus/detik));
  
  Serial.print("  MAX RPM = ");
  Serial.println(rpmMaximum);
}

void displayBar(int rpm)
{
  int numOfBars=map(rpm,0,maxRPM,0,15);

  if (rpm!=0)
  {
  for (int i=0; i<=numOfBars; i++)
   {
     
      }
  }
} 
