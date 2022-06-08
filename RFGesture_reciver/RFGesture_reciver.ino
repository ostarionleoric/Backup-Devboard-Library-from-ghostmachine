
#include <VirtualWire.h>

//motor one
int enA = 5;
int in4 = 9;
int in3 = 8;
// motor two
int enB = 10;
int in1 = 7;
int in2 = 4;
void setup()
{
Serial.begin(9600);
vw_set_ptt_inverted(true); // Required for DR3100
vw_set_rx_pin(12);
vw_setup(4000);  // Bits per sec
pinMode(13, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
vw_rx_start();       // Start the receiver PLL running
Serial.println("All OK");

}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

if (vw_get_message(buf, &buflen)) // Non-blocking
{
if((buf[0]=='X')&&(buf[1]=='1'))
  {   
  Serial.println("BACKWARD");
  backward();
  delay(100);
  //off();
  }  
      
      
else if((buf[0]=='X')&&(buf[1]=='2'))
  {  
  Serial.println("FORWARD");
  forward();
  delay(100);
  //off();
  }

else if((buf[0]=='Y')&&(buf[1]=='1'))
  {  
   Serial.println("LEFT");
   left();
   delay(100);
   //off();
  }

else if((buf[0]=='Y')&&(buf[1]=='2'))
  {  
  Serial.println("RIGHT");
  right();
  delay(100);
  //off();
  }
else if((buf[0]=='A')&&(buf[1]=='1'))
  {  
  Serial.println("STOP");
  off();
  delay(100);
  }
      
}
else
{
  Serial.println("No Signal Received");
}
}


void forward()
{ 

}

void backward()
{ 

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,255);
}

void left()
{ 

 
 digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB,255);
  
}

void right()
{ 

  
digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA,255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB,255);
}

void off()
{ 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA,255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB,255);
}
