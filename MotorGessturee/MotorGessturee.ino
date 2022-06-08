
int ENB10 = 10;
int ENB11 = 11;


int ENA5 = 5;
int ENA6 = 6;

int pin7 = 7;
int pin4 = 4;

int pin8 = 8;
int pin12 =12;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin7, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin12, OUTPUT);
  pinMode(ENB10, OUTPUT);
  pinMode(ENB11, OUTPUT);
  pinMode(ENA5, OUTPUT);
  pinMode(ENA6, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
//MAJU
/*
analogWrite(ENB10, 255);
analogWrite(ENB11, 255);
analogWrite(ENA5, 255);
analogWrite(ENA6, 255);
*/
  /*
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH);
   delay(3500);          
*/

  //STOP atau BERHENTI
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);// wait for a second

  
  //MAJU
  digitalWrite(pin8, HIGH);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, HIGH);    // turn the LED off by making the voltage LOW

  delay(5000);
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, HIGH);
  digitalWrite(pin7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);

  
//STOP LAGI        
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);       

  //BELOK kanan
  digitalWrite(pin8, HIGH);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, LOW);
  delay(5000);
  
  
  //BELOK kiri
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(pin4, LOW);
  delay(1500);       
}
