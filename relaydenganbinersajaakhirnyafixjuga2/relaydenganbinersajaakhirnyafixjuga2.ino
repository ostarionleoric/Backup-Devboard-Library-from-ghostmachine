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
    if(nilaiDayaQ>=952) myport.send_8bit_data(63);
    
    else if(nilaiDayaQ>=692 && nilaiDayaQ<=706) myport.send_8bit_data(46);
    else if(nilaiDayaQ>=677 && nilaiDayaQ<=691) myport.send_8bit_data(45);
    else if(nilaiDayaQ>=662 && nilaiDayaQ<=676) myport.send_8bit_data(44);
    else if(nilaiDayaQ>=647 && nilaiDayaQ<=661) myport.send_8bit_data(43);
    else if(nilaiDayaQ>=632 && nilaiDayaQ<=646) myport.send_8bit_data(42);
    else if(nilaiDayaQ>=616 && nilaiDayaQ<=631) myport.send_8bit_data(41);
    else if(nilaiDayaQ>=601 && nilaiDayaQ<=615) myport.send_8bit_data(40);
    else if(nilaiDayaQ>=586 && nilaiDayaQ<=600) myport.send_8bit_data(39);
    else if(nilaiDayaQ>=571 && nilaiDayaQ<=585) myport.send_8bit_data(38);
    else if(nilaiDayaQ>=555 && nilaiDayaQ<=570) myport.send_8bit_data(37);
    else if(nilaiDayaQ>=540 && nilaiDayaQ<=554) myport.send_8bit_data(36);
    else if(nilaiDayaQ>=525 && nilaiDayaQ<=539) myport.send_8bit_data(35);
    else if(nilaiDayaQ>=510 && nilaiDayaQ<=524) myport.send_8bit_data(34);
    else if(nilaiDayaQ>=494 && nilaiDayaQ<=509) myport.send_8bit_data(33);
    else if(nilaiDayaQ>=481 && nilaiDayaQ<=493) myport.send_8bit_data(32);
    else if(nilaiDayaQ>=465 && nilaiDayaQ<=480) myport.send_8bit_data(31);
    else if(nilaiDayaQ>=449 && nilaiDayaQ<=464) myport.send_8bit_data(30);
    else if(nilaiDayaQ>=433 && nilaiDayaQ<=448) myport.send_8bit_data(29);
    else if(nilaiDayaQ>=419 && nilaiDayaQ<=432) myport.send_8bit_data(28);
    else if(nilaiDayaQ>=403 && nilaiDayaQ<=418) myport.send_8bit_data(27);
    else if(nilaiDayaQ>=388 && nilaiDayaQ<=402) myport.send_8bit_data(26);
    else if(nilaiDayaQ>=373 && nilaiDayaQ<=387) myport.send_8bit_data(25);
    else if(nilaiDayaQ>=358 && nilaiDayaQ<=372) myport.send_8bit_data(24);
    else if(nilaiDayaQ>=343 && nilaiDayaQ<=357) myport.send_8bit_data(23);
    else if(nilaiDayaQ>=328 && nilaiDayaQ<=342) myport.send_8bit_data(22);
    else if(nilaiDayaQ>=312 && nilaiDayaQ<=327) myport.send_8bit_data(21);
    else if(nilaiDayaQ>=297 && nilaiDayaQ<=311) myport.send_8bit_data(20);
    else if(nilaiDayaQ>=282 && nilaiDayaQ<=296) myport.send_8bit_data(19);
    else if(nilaiDayaQ>=266 && nilaiDayaQ<=281) myport.send_8bit_data(18);
    else if(nilaiDayaQ>=251 && nilaiDayaQ<=265) myport.send_8bit_data(17);
    else if(nilaiDayaQ>=236 && nilaiDayaQ<=250) myport.send_8bit_data(16);
    else if(nilaiDayaQ>=221 && nilaiDayaQ<=235) myport.send_8bit_data(15);
    else if(nilaiDayaQ>=206 && nilaiDayaQ<=220) myport.send_8bit_data(14);
    else if(nilaiDayaQ>=191 && nilaiDayaQ<=205) myport.send_8bit_data(13);
    else if(nilaiDayaQ>=176 && nilaiDayaQ<=190) myport.send_8bit_data(12);
    else if(nilaiDayaQ>=161 && nilaiDayaQ<=175) myport.send_8bit_data(11);
    else if(nilaiDayaQ>=145 && nilaiDayaQ<=160) myport.send_8bit_data(10);
    else if(nilaiDayaQ>=130 && nilaiDayaQ<=144) myport.send_8bit_data(9);
    else if(nilaiDayaQ>=114 && nilaiDayaQ<=129) myport.send_8bit_data(8);
    else if(nilaiDayaQ>=99 && nilaiDayaQ<=113) myport.send_8bit_data(7);
    else if(nilaiDayaQ>=84 && nilaiDayaQ<=98) myport.send_8bit_data(6);
    else if(nilaiDayaQ>=69 && nilaiDayaQ<=83) myport.send_8bit_data(5);
    else if(nilaiDayaQ>=54 && nilaiDayaQ<=68) myport.send_8bit_data(4);
    else if(nilaiDayaQ>=38 && nilaiDayaQ<=53) myport.send_8bit_data(3); 
    else if(nilaiDayaQ>=24 && nilaiDayaQ<=37) myport.send_8bit_data(2);
    else if(nilaiDayaQ>=1 && nilaiDayaQ<=23) myport.send_8bit_data(1);
    else myport.send_8bit_data(0); 
   // delay(500);
}
