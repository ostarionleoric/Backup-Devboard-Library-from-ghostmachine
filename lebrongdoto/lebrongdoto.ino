#include<IO_Port_8bit.h>

IO_Port_8bitmyport(2, 3, 4, 5, 6, 7, 8, 9, ’O’); //create output port object

void setup()

{

myport.send_8bit_data(255); //blink all LEDs of bar graph once

delay(500);

myport.send_8bit_data(0);

}

void loop()

{

int level;

level = analogRead(A0); //read analog input voltage

level = map(level, 0, 1023, 0, 80);// limit thevoltage from 0 to 80

//increase or decrease bar graph level asper input

if((level<80) && (level>70))myport.send_8bit_data(255);

elseif((level<=70) && (level>60)) myport.send_8bit_data(127);

elseif((level<=60) && (level>50)) myport.send_8bit_data(63);

elseif((level<=50) && (level>40)) myport.send_8bit_data(31);

elseif((level<=40) && (level>30)) myport.send_8bit_data(15);

elseif((level<=30) && (level>20)) myport.send_8bit_data(7);

elseif((level<=20) && (level>10))myport.send_8bit_data(3);

elseif((level<=10) && (level>0)) myport.send_8bit_data(1);

elseif(level==0) myport.send_8bit_data(0);

}
