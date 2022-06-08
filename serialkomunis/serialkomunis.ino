String str;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 Serial1.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  str =String('H')+String('E')+String('N')+String('T')+String('A')+String('I');
  Serial1.println(str);
  Serial1.println("kecap");
  Serial.println("hentai");
  Serial.println("hentaiyaro");
  Serial.println("hentai");
  delay(1000);
}
