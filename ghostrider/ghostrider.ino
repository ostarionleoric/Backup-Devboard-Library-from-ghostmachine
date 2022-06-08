#include <LiquidCrystal_I2C.h>  
#include <Wire.h>
#include "EmonLib.h" // Include Emon Library
EnergyMonitor emon1;  // Create an instance
LiquidCrystal_I2C lcd (0x3F,20,4);
#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3); // RX | TX

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
 
 //SMS
 int smsTerkirim = 0;
void setup() {
 Serial.begin(9600);
 //lcd.begin();
//PowerFactor
emon1.voltage(2, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
emon1.current(1, 111.1);  // Current: input pin, calibration.
}
void loop() {
  
  //Perhitungan Tegangan pada sensor ZMPT101B
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
  Vrms1=(((VeffD-420.76)/-90.24)*-220); // rumus perhitungan tegangan output dengan menggunakan persamaan garis lurus
 
  VmaxD=0; 
}
//Tampilkan Tegangan
lcd.setCursor(0,1);
lcd.print("V =      V");
lcd.setCursor(3,1);
lcd.print(Vrms1);

//Tampilkan Arus
 rmsAmps();
Serial.print("I=");
Serial.println(ACS1);
lcd.setCursor (0,0);
lcd.print("  ===POWER METER=== ");
lcd.setCursor (12,1);
lcd.print("I =    A");
lcd.setCursor(15,1);
lcd.print(ACS1);

//perhitungan power factor
// Read value from Analog Input Pin 0
emon1.calcVI(20,2000); // Calculate all. No.of half wavelengths (crossings), time-out
float supplyVoltage = emon1.Vrms; //extract Vrms into Variable
float Voltage = (supplyVoltage - 0.3291)/0.9354;
float Irms = emon1.Irms; //extract Irms into Variable
float Current = (Irms - 0.2034)/ 7.6245;
Current = (Current +0.0475)/0.9428;
if(Current <0.17){
Current = 0;
}
float powerFactor = emon1.powerFactor; //extract Power Factor into Variable
float PF = (powerFactor + 2.1112)/2.7216;
PF = (PF-1)/0.2295;
if (powerFactor < 0.2){
powerFactor = 0;
}
lcd.setCursor(0,2); 
lcd.print("Pf=");
lcd.setCursor(3,2); 
lcd.print(powerFactor);


 //Daya
float Daya = supplyVoltage*Current*powerFactor;
int sample = sample + 1;
msec = millis();
time = (float) msec / 1000.0;
float totalCharge = totalCharge + Current;
float averageAmps = totalCharge / sample;
float ampSecond = averageAmps*time;
float ampHour = ampSecond/3600;
float wattHour = Voltage * ampHour * powerFactor;
float wattHourNow = wattHourNow + wattHour;
lcd.setCursor(0,3);  
lcd.print("P =");
lcd.setCursor(3,3);
lcd.print(Daya); //Daya Total  

//perhitungan Kwh
Kwh = ((Daya*12)/1000);
lcd.setCursor(10,3);  
lcd.print("Kwh =");
lcd.setCursor(15,3);
lcd.print(0.33);
Serial.print("Kwh");
Serial.println(Kwh);


// diberikan nilai tunda 1 s untuk pembacaan berikutnya
// Menampilkan pembacaan analog-to-digital converter   setelah pembacaan terakhir
 delay (1000);
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

 void sms() {
  // KIRIM SMS
  Serial.println("ACS1,Vrms1,PowerFactor,Daya,Kwh");
  SIM800L.println("AT+CMGF=1\r\n");
  delay(3000);

  Serial.println("SIM800L Set SMS ke Nomor Tujuan");
  SIM800L.println("AT+CMGS=\"+6282363215546\"\r\n");
  delay(3000);

  Serial.println("SIM800L Send SMS content");
  SIM800L.println("===Power Meter===");
  delay(3000);

  Serial.println("Mengirim Char Ctrl+Z / ESC untuk keluar dari menu SMS");
  SIM800L.println((char)26);
  delay(3000);

  Serial.println("SMS Selesai Dikirim!");
  smsTerkirim = 1;
  delay(5000);
}

//Pemograman Sudut Phasa(cos phi)
void EnergyMonitor::voltage(unsigned int _inPinV, double _VCAL, double _PHASECAL) 
{ 
inPinV = _inPinV; 
VCAL = _VCAL; 
PHASECAL = _PHASECAL; 
offsetV = ADC_COUNTS>>1; 
} 
void EnergyMonitor::current(unsigned int _inPinI, double _ICAL) 
{ 
inPinI = _inPinI; 
ICAL = _ICAL; 
offsetI = ADC_COUNTS>>1; 
} 
// Sets the pins to be used for voltage and current sensors based on emontx pin map 
void EnergyMonitor::voltageTX(double _VCAL, double _PHASECAL) 
{ 
inPinV = 2; 
VCAL = _VCAL; 
PHASECAL = _PHASECAL; 
offsetV = ADC_COUNTS>>1; 
} 
void EnergyMonitor::currentTX(unsigned int _channel, double _ICAL) 
{ 
if (_channel == 1) inPinI = 3; 
if (_channel == 2) inPinI = 0; 
if (_channel == 3) inPinI = 1; 
ICAL = _ICAL; 
offsetI = ADC_COUNTS>>1; 
} 

// emon_calc procedure 
// Calculates realPower,apparentPower,powerFactor,Vrms,Irms,kWh increment 
// From a sample window of the mains AC voltage and current. 
// The Sample window length is defined by the number of half wavelengths or crossings we choose to measure 
void EnergyMonitor::calcVI(unsigned int crossings, unsigned int timeout) 
{ 
#if defined emonTxV3 
int SupplyVoltage=3300; 
#else 
int SupplyVoltage = readVcc(); 
#endif 
unsigned int crossCount = 0; //Used to measure number of times threshold is crossed. 
unsigned int numberOfSamples = 0; //This is now incremented 
// 1) Waits for the waveform to be close to 'zero' (mid-scale adc) part in sin curve. 
boolean st=false; //an indicator to exit the while loop 
unsigned long start = millis(); //millis()-start makes sure it doesnt get stuck in the loop if there is an error. 
while(st==false) //the while loop... 
{ 
startV = analogRead(inPinV); //using the voltage waveform 
if ((startV < (ADC_COUNTS*0.55)) && (startV > (ADC_COUNTS*0.45))) st=true; //check its within range 
if ((millis()-start)>timeout) st = true; 
} 
// 2) Main measurement loop  
start = millis(); 
while ((crossCount < crossings) && ((millis()-start)<timeout)) 
{ 
numberOfSamples++; //Count number of times looped. 
lastFilteredV = filteredV; //Used for delay/phase compensation 
// A) Read in raw voltage and current samples 

sampleV = analogRead(inPinV); //Read in raw voltage signal 
sampleI = analogRead(inPinI); //Read in raw current signal 
// B) Apply digital low pass filters to extract the 2.5 V or 1.65 V dc offset, 
// then subtract this - signal is now centred on 0 counts. 
offsetV = offsetV + ((sampleV-offsetV)/1024); 
filteredV = sampleV - offsetV; 
offsetI = offsetI + ((sampleI-offsetI)/1024); 
filteredI = sampleI - offsetI; 
//  C) Root-mean-square method voltage 
sqV= filteredV * filteredV; //1) square voltage values 
sumV += sqV; //2) sum 
// D) Root-mean-square method current 
sqI = filteredI * filteredI; //1) square current values 
sumI += sqI; //2) sum 
 
// E) Phase calibration 
phaseShiftedV = lastFilteredV + PHASECAL * (filteredV - lastFilteredV); 
// F) Instantaneous power calc  
instP = phaseShiftedV * filteredI; //Instantaneous Power 
sumP +=instP; //Sum 
// G) Find the number of times the voltage has crossed the initial voltage 
// - every 2 crosses we will have sampled 1 wavelength 
// - so this method allows us to sample an integer number of half wavelengths which increases accuracy 
lastVCross = checkVCross; 
if (sampleV > startV) checkVCross = true; 
else checkVCross = false; 
if (numberOfSamples==1) lastVCross = checkVCross; 
if (lastVCross != checkVCross) crossCount++; 
} 
// 3) Post loop calculations  
//Calculation of the root of the mean of the voltage and current squared (rms) 
//Calibration coefficients applied. 
double V_RATIO = VCAL *((SupplyVoltage/1000.0) / (ADC_COUNTS)); 
Vrms = V_RATIO * sqrt(sumV / numberOfSamples); 
double I_RATIO = ICAL *((SupplyVoltage/1000.0) / (ADC_COUNTS)); 
Irms = I_RATIO * sqrt(sumI / numberOfSamples); 
//Calculation power values 
realPower = V_RATIO * I_RATIO * sumP / numberOfSamples; 
apparentPower = Vrms * Irms; 
powerFactor=realPower / apparentPower; 
//Reset accumulators 
sumV = 0; 
sumI = 0; 
sumP = 0; 
