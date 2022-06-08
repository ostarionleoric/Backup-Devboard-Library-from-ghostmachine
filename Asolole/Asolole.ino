
int ENB10 = 10;
int ENB11 = 11;


int ENA5 = 5;
int ENA6 = 6;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(ENB10, OUTPUT);
  pinMode(ENB11, OUTPUT);
  pinMode(ENA5, OUTPUT);
  pinMode(ENA6, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
//Kecepatannya dalam PWM jancuk
analogWrite(ENB10, 250);
analogWrite(ENB11, 250);
analogWrite(ENA5, 250);
analogWrite(ENA6, 250);

//majunya
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH);
   delay(3500);          


  //STOP atau BERHENTI
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);// wait for a second

  
  //MUNDUR
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(8, HIGH);
  digitalWrite(12, LOW);
  delay(1500);

  
//STOP LAGI        
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);    // turn the LED off by making the voltage LOW
  delay(4000);       

  //BELOK
  digitalWrite(8, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);
  delay(1500);
  
  
  //BELOK
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(7, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(4, LOW);
  delay(1500);       
}
