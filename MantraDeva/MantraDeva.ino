// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

//sensor tegangan 
const int analogIn = A0;
double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Vrms1;

//sensor acs
const int currentPin1 = A1;
const unsigned long sampleTime = 10000UL; 
const unsigned long numSamples = 250UL;
const unsigned long sampleInterval = sampleTime/numSamples;
const int adc_zero = 511.5; 
float result1;
float ACS1=0;

 //power factor,daya dan Kwh
 double PowerFactor;
 double Daya;
 double Kwh;
 


void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 111.1);       // Current: input pin, calibration.
  
}

void loop()
{
  //sampah
  //emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
 // float realPower       = emon1.realPower;        //extract Real Power into variable
  //float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  //float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  //float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  //float Irms            = emon1.Irms;             //extract Irms into Variable
sensorValue1=sensorValue;
// delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){ // rumus perhitungan tegangan output
  climbhill=1;
  VmaxD=sensorValue;
}
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
    VmaxD=sensorValue1;
   VeffD= (VmaxD/sqrt(2));
  Vrms1=(((VeffD-420.76)/-90.24)*-220)+220; // rumus perhitungan tegangan output dengan menggunakan persamaan garis lurus
 
  VmaxD=0; 
    //emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

}
  Serial.print("V=");
Serial.println(Vrms1);

  rmsAmps();
Serial.print("I=");
Serial.println(ACS1);

float powerFactor = emon1.powerFactor; //extract Power Factor into Variable
float PF = (powerFactor + 2.1112)/2.7216;
PF = (PF-1)/0.2295;
if (powerFactor < 0.2){
powerFactor = 0;
}
Serial.print("PF=");
Serial.println(powerFactor);

emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
float supplyVoltage = emon1.Vrms; //extract Vrms into Variable
float Voltage = (supplyVoltage - 0.3291)/0.9354;
float Irms = emon1.Irms; //extract Irms into Variable
float Current = (Irms - 0.2034)/ 7.6245;
Current = (Current +0.0475)/0.9428;
if(Current <0.17){
Current = 0;
}

 
}


float rmsAmps ()
 { 
  float result;
 unsigned long currentAcc1 = 0;
 unsigned int count1 = 0;
 unsigned long prevMicros = micros() - sampleInterval;
 
 while (count1< numSamples)// ulangi eksekusi koding di bawah
 // dalam satu blok {} selama kondisi (0<50)
    {
    if (micros() - prevMicros >= sampleInterval)
      {
       long adc_raw1 = analogRead(currentPin1) - adc_zero;
       currentAcc1 += (unsigned long)(adc_raw1 * adc_raw1);
       ++count1;
       prevMicros += sampleInterval;
      }
    } 
 result1 = (sqrt((float)currentAcc1/(float)numSamples)*(75.757576/1023.0));
 if (result1<=0.1){
 result1 = 0;
  }


//pembacaan arus real//
ACS1 = result1;

 }
