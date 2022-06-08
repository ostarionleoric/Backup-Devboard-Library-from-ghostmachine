const int button = 4;            // GPIO 8 for the button
const int led =13;                // GPIO 7 for the LED
int ledflag=0;                   // LED status flag
const int PinSensorWaterFlowTaman=2;// intr 0 // pin 2
float flow_countertaman,litertaman;
 #include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
   pinMode(PinSensorWaterFlowTaman, INPUT);
        digitalWrite(PinSensorWaterFlowTaman, HIGH);
        attachInterrupt(0, flowtaman, RISING); // Setup Interrupt 0 pada pin 2
 
  pinMode(button,INPUT);         // define button as an input 
  pinMode(led,OUTPUT);           // define LED as an output
  digitalWrite(led,LOW);         // turn output off just in case
Serial.begin(9600);
}

void loop() {
  
int mililiter = litertaman * 1000;
  if (digitalRead(button)==HIGH){ // if button is pressed
    
    if (ledflag==0) {             // and the status flag is LOW
      ledflag=1;                  // make status flag HIGH
      digitalWrite(led,HIGH);     // and turn on the LED
      //flow_countertaman=0;
      }                           // 
    else{                        // otherwise...
      // and turn off the LED
    }
                     // wait a sec for the 
  }
  else if(mililiter >=1000){
          ledflag=0;                  // make status flag LOW
      digitalWrite(led,LOW);
      //delay(10000);
      //flow_countertaman=0;
      //delay(5000);
      
  }
   delay(50);
   Serial.println(litertaman);
  Serial.print("MILILITER = ");
 Serial.println(mililiter);

  lcd.setCursor(0,0);
  lcd.print(mililiter);
  lcd.setCursor(2,1);
  //lcd.print(mililiter);
   lcd.setCursor(0,2);
  //lcd.print("Arduino LCM IIC 2004");
   //lcd.setCursor(2,3);
  //lcd.print("Power By Ec-yuan!");

}              

void flowtaman () // Interrupt function taman
    {
      flow_countertaman++;
       litertaman=flow_countertaman/350;
}