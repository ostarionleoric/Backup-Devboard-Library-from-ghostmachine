#include <EmonLib.h>

 double PowerFactor;
 double Daya;
 double Kwh;
 EnergyMonitor emon1;



//Kumpulan variabel Sensor tegangan, Culween's Most Cunning Fabrications!!!

double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;

//Kumpulan variabel Sensor tegangan, Wex magnelectros!

 const int currentPin = A1;
 const unsigned long sampleTime = 100000UL;
 const unsigned long numSamples = 250UL;
 const unsigned long sampleInterval = sampleTime/numSamples;
 const int adc_zero = 510;
 



void setup() {
emon1.voltage(0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
emon1.current(1, 111.1);  // Current: input pin, calibration.

Serial.begin(9600);
}
void loop() {

//emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
//float supplyVoltage = emon1.Vrms; //extract Vrms into Variable
//float Voltage = (supplyVoltage - 0.3291)/0.9354;
//float Irms = emon1.Irms; //extract Irms into Variable
//float Current = (Irms - 0.2034)/ 7.6245;
//Current = (Current +0.0475)/0.9428;
//if(Current <0.17){
//Current = 0;
//}
float powerFactor = emon1.powerFactor; //extract Power Factor into Variable
float PF = (powerFactor + 0.1112)/0.7216;
PF = (PF-1)/0.2295;
if (powerFactor < 0.2){
powerFactor = 0;
}

//Logika Berpikir untuk sensor tegangan,  Harlek's Incantation of Incineration!!

sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }

//perintah cetak nilai NOL kalo sensor ni ga bisa baca apa apa atau waktu nilai analognya 513  
if ( VmaxD == 513.0  ){
  Serial.println("0 Volt");
  delay(100);
  }
  
//perintah baca, konversi dan cetak nilai tegangan berdasarkan nilai pembacaan sensor
if (sensorValue<sensorValue1 && climbhill==1 && VmaxD>514.0 ){

//variabel arus masuk sini juga, jadi sekalian di cetak bareng nilai tegangan kalo kondisi teganan
  
  double current = rmsAmps(); //ini variable untuk nilai arus
  Serial.print(current); //ini perintah cetak nilai arus
  Serial.println(" Ampere \t");

//nah kalo yang ini alur konversi nilai tegangan, paan da gapenting, skip skip  
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-220.0)+220.0;
  Serial.print(Veff);
  Serial.println(" Volt");

    Serial.print("nilai cos phi nya : ");
    Serial.println(powerFactor);

  //Serial.println(VmaxD);
  VmaxD=0;
  }
}

//nah kalo yang dibawah ini alur konversi nilai tegangan, caritau sendiri males ngatik panjang capek 
float rmsAmps()
 { 
 float result;  
 unsigned long currentAcc = 0;
 unsigned int count = 0;
 unsigned long prevMicros = micros() - sampleInterval;
 while (count < numSamples)
 {
   if (micros() - prevMicros >= sampleInterval)
   {
     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     ++count;
     prevMicros += sampleInterval;
   }
 } 
 result = (sqrt((float)currentAcc/(float)numSamples)*(77.5/1023.0));

 result -=0.10;
 if (result<0.3){result = 0;}
 return result;
 }
 
