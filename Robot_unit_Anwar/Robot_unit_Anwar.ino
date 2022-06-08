
//Library untuk komunikasi antara modul bluetoorh dan arduino
#include <SoftwareSerial.h>

//pin arduino yang digunakan untuk komunikasi bluetooth
#define tx 2
#define rx 3
SoftwareSerial bt(rx, tx); //RX, TX


int ENB10 = 10;
int ENB11 = 11;


int ENA5 = 5;
int ENA6 = 6;


//Pin motor DC
int pin7 = 7;
int pin4 = 4;

//Pin Motor DC
int pin8 = 8;
int pin12 =12;


char d=0;

void setup()
{



//Memulai komunikasi serial antara bluetooth dan arduino dengan baudrate 115200 untuk arduino dan 38400 untuk 
  Serial.begin(115200);
  bt.begin(38400);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  
//Inisiasi pin yang digunakan untuk Driver Motor DC  
  pinMode(pin7, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin12, OUTPUT);
  pinMode(ENB10, OUTPUT);
  pinMode(ENB11, OUTPUT);
  pinMode(ENA5, OUTPUT);
  pinMode(ENA6, OUTPUT);
  
//Memanggil Fungsi Berhenti untuk memastikan robot dalam keadaan off saat pertama kali dinyalakan
 berhenti();
}
void loop()
{
  
  //Mendeteksi apakah Robot sudah terkoneksi dengan remote control
  
  
  if(bt.available()>0)
  {
   //Mencetak nilai yang dikirim memalui komunikasi serial atara robot dan remot
    Serial.println(bt.read());
    
    //Variable untuk membaca nilai yang dikirimkan oleh remot kepada robot
    d=bt.read();
  
  if(d=='F')//Jika Variable d membaca nilai F maka robot mundur
  {
   mundur();
    }
    if(d=='B')//Jika Variable d membaca nilai B maka robot maju
  {
   maju();
    }
    
  if(d=='L')//Jika Variable d membaca nilai L maka robot belok kiri
  {
   kiri();
    }
  if(d=='R')//Jika Variable d membaca nilai R maka belok kanan
  { 
  kanan();
   }
     if(d=='S')//Jika Variable d membaca nilai S maka robot berhenti
  {
   berhenti();
    }
   
}
  
}


/*
Dibawah ini merupakan fungsi fungsi yang dipanggil berdasarkan nilai yang dibaca oleh Variable d
*/


//Fungsi memutar motor robot untuk maju
void maju()
  {
  digitalWrite(pin8, HIGH);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   
  digitalWrite(pin4, HIGH);  
  } 
 
//Fungsi memutar motor robot untuk mundur 

void mundur()
  {
  digitalWrite(pin8, LOW);
  digitalWrite(pin12,HIGH);
  digitalWrite(pin7, HIGH);   
  digitalWrite(pin4, LOW);  

  }

//Fungsi memutar motor robot untuk belok kiri
  void kiri()
  {
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);  
  digitalWrite(pin4, HIGH);
  }
 
//Fungsi memutar motor robot untuk belok kanan
void kanan()
  {
  digitalWrite(pin8, HIGH);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   
  digitalWrite(pin4, LOW);
  }  

////Fungsi untuk menghentikan putaran motor robot
    void berhenti()
  {
  digitalWrite(pin8, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin7, LOW);   
  digitalWrite(pin4, LOW);
  }  
    
    
    
  
  
