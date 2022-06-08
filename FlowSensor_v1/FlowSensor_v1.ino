const int PinSensorWaterFlowTaman=2;// intr 0 // pin 2
float flow_countertaman,litertaman;
const int PinKranTaman =9;//// kran untuk taman
void setup()
{
 pinMode(PinSensorWaterFlowTaman, INPUT);
        digitalWrite(PinSensorWaterFlowTaman, HIGH);
        attachInterrupt(0, flowtaman, RISING); // Setup Interrupt 0 pada pin 2
 Serial.begin(9600);
  pinMode(PinKranTaman,OUTPUT);
        digitalWrite(PinKranTaman,LOW);

}

void loop()
{
 //Serial.println(flow_countertaman);
 int mililiter = litertaman * 1000;
 Serial.println(litertaman);
  Serial.print("MILILITER = ");
 Serial.println(mililiter);
//delay(1000);
} 

void flowtaman () // Interrupt function taman
    {
      flow_countertaman++;
       litertaman=flow_countertaman/350;
}
