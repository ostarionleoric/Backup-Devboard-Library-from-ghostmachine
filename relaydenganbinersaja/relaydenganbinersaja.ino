#include<IO_Port_8bit.h>

IO_Port_8bit myport(2,3,4,5,6,7,8,9,0);
void setup() 
{
  Serial.begin(9600);
  myport.send_8bit_data(255);
  delay(500);
  myport.send_8bit_data(0);
}

void loop() 
{
   int level;
   level = analogRead(A0);
   //level = map(level,0,1023,0,80);
   int nilaiDayaQ=level*0.97;
   Serial.println(nilaiDayaQ);
    if(nilaiDayaQ>900) myport.send_8bit_data(63);
    else if((nilaiDayaQ<80) && (nilaiDayaQ>70)) myport.send_8bit_data(127); 
    else if((nilaiDayaQ<=70) && (nilaiDayaQ>60)) myport.send_8bit_data(63); 
    else if((nilaiDayaQ<=60) && (nilaiDayaQ>50)) myport.send_8bit_data(31);
    else if((nilaiDayaQ<=50) && (nilaiDayaQ>40)) myport.send_8bit_data(15);
    else if((nilaiDayaQ<=40) && (nilaiDayaQ>30)) myport.send_8bit_data(7); 
    else if((nilaiDayaQ<=30) && (nilaiDayaQ>20)) myport.send_8bit_data(3);
    else if(nilaiDayaQ>=1 && nilaiDayaQ<=23) myport.send_8bit_data(1); 
   // delay(500);
}
