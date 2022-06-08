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
Serial.begin(9600);
}
void loop() {
sensorValue1=sensorValue;
delay(100);
sensorValue = analogRead(A0);
if (sensorValue>sensorValue1 && sensorValue>511){
  climbhill=1;
  VmaxD=sensorValue;
  }
if ( VmaxD == 513.0  ){
  Serial.println("0 Volt");
  delay(100);
  }

if (sensorValue<sensorValue1 && climbhill==1 && VmaxD>514.0 ){
  double current = rmsAmps();
  Serial.println(current);
  climbhill=0;
  VmaxD=sensorValue1;
  VeffD=VmaxD/sqrt(2);
  Veff=(((VeffD-420.76)/-90.24)*-220.0)+220.0;
  Serial.print(Veff);
  Serial.println(" Volt");
  //Serial.println(VmaxD);
  VmaxD=0;
  }
 
//arus yang ditampilkan (current) adalah sama dengan arus rmsAmps()
 
// delay(500); 
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
 
