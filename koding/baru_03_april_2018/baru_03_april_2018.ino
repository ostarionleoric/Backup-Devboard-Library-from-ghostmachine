
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

double sensorValue=0;
double sensorValue1=0;
int crosscount=0;
int climbhill=0;
double VmaxD=0;
double VeffD;
double Veff;

 
 const int currentPin = A1;
 const unsigned long sampleTime = 100000UL;
 //sample over 100ms, it is an exact number of cycles for both 50Hz and 60Hz mains
 const unsigned long numSamples = 250UL;
 //choose the number of samples to divide sampleTime exactly, but low enough for the ADC to keep up
 const unsigned long sampleInterval = sampleTime/numSamples;
 //the sampling interval, must be longer than then ADC conversion time
 const int adc_zero = 510;
 //relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
 //Penjelasan tentang penggunaan UL = 
 //Integer konstanta adalah angka yang digunakan secara langsung dalam sketsa, seperti 123. Secara default,
 //angka-angka ini diperlakukan sebagai int tapi Anda dapat mengubahnya dengan pengubah U dan L
//unsigned long adalah bilangan bulat positif yang dapat memiliki nilai hingga 4.294.967.295
 
void setup() {
bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }

  
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial.println("Hasil Pembacaan Sensor Tegangan dan Arus");
 delay(100);
}

void loop() {
sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);

if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }
if (sensorValue<sensorValue1 && climbhill==1){
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-210.2)+210.2;
//  Serial.print(Veff);
  //Serial.println();
  VmaxD=0;
}




  
  // put your main code here, to run repeatedly:
double current = rmsAmps();
//arus yang ditampilkan (current) adalah sama dengan arus rmsAmps()
float Daya = current*Veff;
 
 
 Serial.print("Arus=");
 Serial.println(current);
 delay(500);
 Serial.print("Tegangan=");
 delay(100);
 Serial.print(Veff);
  Serial.println();
 delay(500);  

 Serial.print("Daya=");
 Serial.println(Daya);
 delay(500);
}
float rmsAmps()
//method atau tempat pengolahan nilai arus adalah rmsAmps()
//isi dalam method adalah dibawah ini
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
 //untuk menampilkan arus
 result -=0.10;
 if (result<0.3){result = 0;}
 return result;

  
 }

 bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
 

