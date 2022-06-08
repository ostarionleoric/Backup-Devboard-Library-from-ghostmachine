//declaration of variables
int relay1=A0;
int relay2=A1;

int manAuto=6;
int PLNgenset=7;

int manualLed=3;
int autoLed=2;
int GensetLed=4;
int PLNLed=5;

int input1=8;  //Genset
int input2=9;  //PLN
boolean autoManualStatus=true;
boolean PLNgensetStatus=false;
// Function prototypes
void systemInit();
void checkAutoManual();
void checkPLNgenset();
void manLedOn();
void manLedOff();
void autoLedOn();
void autoLedOff();
void PLNLedOn();
void PLNLedOff();

void systemInit(){
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  pinMode(manualLed,OUTPUT);
  pinMode(autoLed,OUTPUT);
  pinMode(GensetLed,OUTPUT);
  pinMode(PLNLed,OUTPUT);
  pinMode(manAuto,INPUT_PULLUP);
  pinMode(PLNgenset,INPUT_PULLUP);
  pinMode(input1,INPUT);
  pinMode(input2,INPUT);
  Serial.begin(9600);
  Serial.println("started");
  
}

void setup() {
  systemInit();
}

void loop() {
 checkAutoManual();
 checkPLNgenset();
  //automanualstatus false manual mode
  //PLNgensetstatus true   grid mode
  //PLNgensetstatus false  solar mode
  if(!autoManualStatus){
    delay(100);
    Serial.println("Manual status");
    autoLedOff();
    manLedOn();
  if(PLNgensetStatus)
   {
     delay(1000);
     Serial.println("Grid Manual");
     relay1Off();
     relay2On();
     GensetLedOn();
     PLNLedOff();
      
    }
     if(!PLNgensetStatus)
    {
      delay(1000);
      //Serial.println("Solar Manual");
      relay1On();
      relay2Off(); 
      PLNLedOn();
      GensetLedOff();
    }
    
  }

  
//  automanualstatus true  automode
  if(autoManualStatus){
    checkinputauto();
    delay(1000);
    //Serial.println("Automatic mode");
    autoLedOn();
    manLedOff();
    
  }
  
  // put your main code here, to run repeatedly:

}
void manLedOn(){
  digitalWrite(manualLed,HIGH);
}
void manLedOff(){
  digitalWrite(manualLed,LOW);
}
void autoLedOn(){
  digitalWrite(autoLed,HIGH);
}
void autoLedOff(){
  digitalWrite(autoLed,LOW);
}
void GensetLedOn(){
  digitalWrite(GensetLed,HIGH);
}
void GensetLedOff(){
  digitalWrite(GensetLed,LOW);
}
void PLNLedOn(){
  digitalWrite(PLNLed,HIGH);
}
void PLNLedOff(){
  digitalWrite(PLNLed,LOW);
}
void relay1Off(){
  digitalWrite(relay1,HIGH);
}
void relay1On(){
  digitalWrite(relay1,LOW);
}
void relay2Off(){
  digitalWrite(relay2,HIGH);
}
void relay2On(){
  digitalWrite(relay2,LOW);
}
void checkinputauto(){
  autoLedOn();
  if((digitalRead(input1)==HIGH)&&(digitalRead(input2)==HIGH)){ ////SWITCH TO SOLAR
    relay1Off();
    relay2On();
    PLNLedOn();
    GensetLedOff();
    delay(100); Serial.println("MODE PLN");delay(1000);
  }
   if(digitalRead(input1)==HIGH&&digitalRead(input2)==LOW){ //SWITCH TO grid
    relay1On();
    relay2Off();
    GensetLedOn();
    PLNLedOff();
    delay(100); Serial.println("MODE GENSET");delay(1000);
  }
   if(digitalRead(input1)==LOW&&digitalRead(input2)==HIGH){  //SWITCH TO SOLAR
    relay1Off();
    relay2On();
    PLNLedOn();
    GensetLedOff();
    delay(100); Serial.println("MODE PLN (hanya PLN)");delay(1000);
  }
   if(digitalRead(input1)==LOW&&digitalRead(input2)==LOW){  //SYSTEM WONT WORK IN THE FIRST PLACE
    //DO NOTHING
      relay1Off();
      relay2Off();
    //  manLedOn();
    //  delay(200);
    //  manLedOff();
    //  delay(200);
     
      
      GensetLedOn();
      delay(200);
      GensetLedOff();
      delay(200);
      PLNLedOn();
     delay(200);
      PLNLedOff();
       Serial.println("Tidak Ada Sumber");
      delay(200);
   
  }
}
void checkAutoManual(){
  if(digitalRead(manAuto)==LOW)
  {
    
   autoManualStatus=!autoManualStatus;
    delay(300);
  }
}
void checkPLNgenset(){
   if(digitalRead(PLNgenset)==LOW)
  {
   
    PLNgensetStatus=!PLNgensetStatus;
    delay(300);
  }
  
}
