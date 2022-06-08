int kambing=12;
int lembu=11;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(kambing,OUTPUT);
  pinMode(lembu,OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
  
  digitalWrite(kambing, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(4000);                       // wait for a second
  digitalWrite(kambing, LOW);    // turn the LED off by making the voltage LOW
  delay(4000);                       // wait for a second

  
  digitalWrite(lembu, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(6000);                       // wait for a second
  digitalWrite(lembu, LOW);    // turn the LED off by making the voltage LOW
  delay(6000);                       // wait for a second
}
