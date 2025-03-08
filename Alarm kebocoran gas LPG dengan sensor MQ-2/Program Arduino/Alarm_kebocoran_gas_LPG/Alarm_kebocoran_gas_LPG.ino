/*
Lisensi Herian

Hak Cipta (c) 2025, Herian

Diberikan izin kepada siapa saja untuk menggunakan, menyalin, memodifikasi, dan mendistribusikan kode ini dengan syarat:
1. Pemberitahuan hak cipta ini tetap dipertahankan.
2. Perangkat lunak disediakan "apa adanya", tanpa jaminan apa pun.
3. Pengguna bertanggung jawab atas segala risiko penggunaan.

*/

float vinSensor;
int adc;
byte kedip;

void setup(){ 
//  Serial.begin(9600);
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);  
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW); 
  do{
    adc = analogRead(A0);
    vinSensor = adc * (5.0 / 1023.0);  
    digitalWrite(9,LOW);   
    delay(100);     
    digitalWrite(9,HIGH);   
    delay(100);     
  }
  while(vinSensor > 1.50);
  digitalWrite(9,LOW);   
}

void loop(){
  adc = analogRead(A0);
  vinSensor = adc * (5.0 / 1023.0);

//  Serial.println(vinSensor);
//  Untuk menampilkan hasil pembacaan sensor, hilangkan
//  tanda komentar pada Serial.
//  Kepekaan pembacaan sensor dapat disesuaikan dengan
//  merubah nilai perbandingan 1.5V.

  if (vinSensor > 1.5){
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);  
    delay(1000);
    do{
      adc = analogRead(A0);
      vinSensor = adc * (5.0 / 1023.0);    
    }
    while(vinSensor > 1.00);
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);  
  }
  
  if (kedip < 20){
    digitalWrite(9,HIGH);
  }
  else if(kedip < 200){
    digitalWrite(9,LOW);
  }
  else{
    kedip = 0;
  }
  kedip++;
  delay(10);
}