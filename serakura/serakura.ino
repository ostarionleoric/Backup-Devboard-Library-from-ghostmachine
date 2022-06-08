const int input_sensor = A0; // nama lain dari A0 yaitu input_sensor
//const int output_pwm = 2; // nama lain dari 2 yaitu output_pwm
 
//nilai default variabel data
int hasil_sensor = 00;    
//int nilai_pwm = 00;    
float voltageOut= 00;
float voltage= 00;
float Veronica=00;
float vegapunk=00;
 
void setup() {
  // inisialisasi komunikasi serial pada 960bps
  Serial.begin(115200); 
}
 
void loop() {
  hasil_sensor = analogRead(input_sensor); // Prosedur pembacaan analog pin           
  // mapping pembacaan resolusi sensor
  //nilai_pwm = map(hasil_sensor, 00, 1023, 00, 255);  
  // mengubah nilai analog out
  //analogWrite(output_pwm, nilai_pwm);    
 voltageOut = (hasil_sensor )/ 1023.00*5.00 ;  
 Veronica=voltageOut/sqrt(2);
 voltage = (voltageOut+1.78)/0.01;   
 vegapunk=Veronica/0.01;
  // Mencetak hasil ke monitor serial:
  //Serial.print("sensor = " );                       
  //Serial.print(hasil_sensor);      
  //Serial.print("output = ");      
  //Serial.println(nilai_pwm);   
  //Serial.print("Voltage ADC = ");      
  //Serial.println(voltageOut);
  //Serial.print("Voltage = ");      
  //Serial.println(voltage);
  Serial.println(hasil_sensor);
  delay(100);  //jeda 2ms                   
}
