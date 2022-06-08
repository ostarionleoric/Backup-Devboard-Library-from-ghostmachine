/*  * Project : Interfacing MX1508 Motor Driver Module with Arduino and pushing commands through serial monitor  
* Website: www.etechpath.com  
* Author: PranaySS (Admin)  
* Link :  http://www.etechpath.com/how-to-use-l298n-motor-driver-module-to-drive-a-dc-motor-using-arduino-mx1508-1627hs/  
* Video : https://youtu.be/oUAaZGauyhU  
*/ 

 void setup() {   
Serial.begin(9600);   
pinMode(50, OUTPUT);   
pinMode(52, OUTPUT);   
pinMode(7, OUTPUT);   
pinMode(6, OUTPUT);   
Print_Instructions();    
 }
  void loop() 
{   
char x;      
while(Serial.available())   
{     x = Serial.read();     
digitalWrite(50, LOW);     
digitalWrite(52, LOW);      
if (x =='1')     
{        FD();     }    
 else if(x =='2')     
{       RV();     }     
else if(x =='3')     
{       ST();     }    
 else     
{       Serial.println("Invalid Input, Try Again");       
delay(100);       
Print_Instructions();     
}   
}
 }  

void Print_Instructions()  
{   
Serial.println("Enter number 1, 2 or 3 to control Motor:"); 
  Serial.println("1. FORWARD");   
Serial.println("2. REVERSE");   
Serial.println("3. STOP");   
Serial.println();   
}  
void FD() 
{   
digitalWrite(50, HIGH);
digitalWrite(52, LOW);   
digitalWrite(7, HIGH);   
digitalWrite(6, LOW);     
Serial.println("Motor 1&2 Forward");   
Serial.println(); 
}  
void RV()
 {   
digitalWrite(50, LOW);    
digitalWrite(52, HIGH);   
digitalWrite(7, LOW);    
digitalWrite(6, HIGH);   
Serial.println("Motor 1&2 Reverse");   
Serial.println(); 
}  
void ST()
 {     
digitalWrite(50, LOW);     
digitalWrite(52, LOW);     
digitalWrite(7, LOW);     
digitalWrite(6, LOW);     
Serial.println("Motor 1&2 Stop");     
Serial.println();  
}
