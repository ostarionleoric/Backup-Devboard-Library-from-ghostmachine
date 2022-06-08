 
const int input_sensor = A0; // nama lain dari A0 yaitu input_sensor
int hasil_sensor = 00;    
//int nilai_pwm = 00;    
float voltageOut= 00;
float voltage= 00;
 
void setup() {
  Serial.begin(9600); 
}
 
void loop() {
  hasil_sensor = analogRead(input_sensor); // Prosedur pembacaan analog pin           
 // nilai_pwm = map(hasil_sensor, 00, 1023, 00, 255);  
  voltageOut = (hasil_sensor / 1023.0)*5.0 ;  
  voltage = (voltageOut-0.5)/0.01;   
  //Serial.print("sensor = " );                       
  //Serial.println(hasil_sensor);      
  //Serial.print("output = ");      
  //Serial.println(nilai_pwm);   
  Serial.print("Voltage ADC = ");      
  Serial.println(voltageOut);
  Serial.print("Voltage = ");      
  Serial.println(voltage);
  delay(100);  //jeda 2ms                   
}
