 #include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);        // atur alamat LCD ke 0x27 untuk tampilan 16 karakter dan 2 baris

void setup()
{
  lcd.init();                                   // inisialisasi lcd
  lcd.backlight();                        // untuk menampilkan pencahayaan pada lcd
}          
void loop()
{
  lcd.setCursor(0,0);                              // untuk menampilkan karakter dari kolom 0 dan baris 0
  lcd.print("      SELAMAT");       // untuk menampilkan tulisan ke lcd
  lcd.scrollDisplayRight ();         // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1300);                              // delay saat tulisan berjalan
  lcd.clear ();                   

  lcd.setCursor(0,1);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("     HARI RAYA");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1100);                                // delay saat tulisan berjalan
  lcd.clear ();                   


  lcd.setCursor(0,2);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("    IDUL FITRI ");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1200);                                // delay saat tulisan berjalan
  lcd.clear ();

  lcd.setCursor(0,3);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("   1441 HIJRIAH ");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1200);                                // delay saat tulisan berjalan
  lcd.clear ();

  lcd.setCursor(0,0);                              // untuk menampilkan karakter dari kolom 0 dan baris 0
  lcd.print("    Mohon Maaf");       // untuk menampilkan tulisan ke lcd
  lcd.scrollDisplayRight ();         // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1500);                              // delay saat tulisan berjalan
  lcd.clear ();   

  lcd.setCursor(0,1);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("  Lahir dan batin");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1200);                                // delay saat tulisan berjalan
  lcd.clear (); 
  lcd.setCursor(0,2);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("       atas ");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1000);                                // delay saat tulisan berjalan
  lcd.clear ();

  lcd.setCursor(0,3);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("  Segala kesalahan ");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1600);                                // delay saat tulisan berjalan
  lcd.clear ();

  lcd.setCursor(0,0);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("Semoga amalan kita");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1500);                                // delay saat tulisan berjalan
  lcd.clear ();

    lcd.setCursor(0,1);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("    Selama ini");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1200);                                // delay saat tulisan berjalan
  lcd.clear ();

    lcd.setCursor(0,2);                              // untuk menampilkan karakter dari kolom 0 dan baris 0
  lcd.print("     diterima");       // untuk menampilkan tulisan ke lcd
  lcd.scrollDisplayRight ();         // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1200);                              // delay saat tulisan berjalan
  lcd.clear ();  
  
    lcd.setCursor(0,3);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("       Oleh");       // untuk menampilkan tulisan di lcd
  lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (1000);                                // delay saat tulisan berjalan
  lcd.clear (); 

  
  lcd.setCursor(0,1);                      // untuk menampilkan karakter dari kolom 0 dan baris 1
  lcd.print("        ALLAH ");       // untuk menampilkan tulisan di lcd
  lcd.setCursor(0,2);
  lcd.print("  Subhanahuwata'ala");
  //lcd.scrollDisplayRight ();           // untuk menampilkan tulisan berjalan dari arah kanan
  delay (5000);                                // delay saat tulisan berjalan
  lcd.clear ();
}
