/*
Lisensi Herian

Hak Cipta (c) 2025, Herian

Diberikan izin kepada siapa saja untuk menggunakan, menyalin, memodifikasi, dan mendistribusikan kode ini dengan syarat:
1. Pemberitahuan hak cipta ini tetap dipertahankan.
2. Perangkat lunak disediakan "apa adanya", tanpa jaminan apa pun.
3. Pengguna bertanggung jawab atas segala risiko penggunaan.

*/

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

static const int RXPin = 8, TXPin = 9;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  lcd.init(16, 2);
  lcd.print("Interfacing GPS");
  lcd.setCursor(0, 1);
  lcd.print("  dg Arduino");
  delay(2000);
  lcd.clear();
  lcd.print("Baca Lokasi GPS");
  delay(2000);
}

void loop(){
  while (ss.available() > 0)
  if (gps.encode(ss.read())) displayInfo();
  if (millis() > 5000 && gps.charsProcessed() < 10){
    lcd.clear();
    lcd.print("No GPS detected:");
    lcd.setCursor(0,1);
    lcd.print("check wiring.");
    while(true);
  }
}

void displayInfo(){ 
  if (gps.location.isValid()){
    lcd.setCursor(0, 0);
    lcd.print(gps.location.lat(), 6);
    lcd.print(" LS   ");
    lcd.setCursor(0, 1);
    lcd.print(gps.location.lng(), 6);
    lcd.print(" BT   ");
  }
  else{
    lcd.clear();
    lcd.print("INVALID");
  }
  delay(500);
}
