/*
 * Dual Temperature Sensor Display (DS18B20 & LM35)
 * Copyright (c) 2025 Herian
 *
 * Licensed under the MIT License.
 * You are free to use, modify, and distribute this code, 
 * but you must include this copyright notice.
 */

 #include <OneWire.h>
 #include <Wire.h>
 #include <LiquidCrystal.h>
 
 LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 OneWire  ds(10);  // on pin 10 --DS1820
 
 unsigned int adc,tempDS,tempLM;
 
 void setup(void) {
   lcd.begin(16, 2);
   lcd.print("2Ch Sensor Suhu");
   lcd.setCursor(0,1);  
   delay(1000);  
 }
 
 void loop(void) {
   byte i;
   byte present = 0;
   byte type_s;
   byte data[12];
   byte addr[8];
   float celsius, fahrenheit;
 
   if (!ds.search(addr)) {
     ds.reset_search();
     delay(250);
     return;
   }
 
   switch (addr[0]) {
     case 0x10: type_s = 1; break;  // DS18S20 atau DS1820
     case 0x28: // DS18B20
     case 0x22: type_s = 0; break;  // DS1822
     default: return;
   }
 
   ds.reset();
   ds.select(addr);
   ds.write(0x44, 1);  
 
   delay(1000);  
 
   present = ds.reset();
   ds.select(addr);    
   ds.write(0xBE);
 
   for (i = 0; i < 9; i++) {
     data[i] = ds.read();
   }
 
   int16_t raw = (data[1] << 8) | data[0];
   if (type_s) {
     raw = raw << 3;
     if (data[7] == 0x10) {
       raw = (raw & 0xFFF0) + 12 - data[6];
     }
   } else {
     byte cfg = (data[4] & 0x60);
     if (cfg == 0x00) raw = raw & ~7;  
     else if (cfg == 0x20) raw = raw & ~3;  
     else if (cfg == 0x40) raw = raw & ~1;  
   }
 
   celsius = (float)raw / 16.0;
   fahrenheit = celsius * 1.8 + 32.0;
   tempDS = celsius;
 
   adc = analogRead(0);   
   tempLM = (adc * 5) / 10;
 
   lcd.setCursor(0,1);  
   lcd.print("T1:");
   lcd.print(tempDS);
   lcd.write(0xDF);
   lcd.print("C, T2:");  
   lcd.print(tempLM);
   lcd.write(0xDF);
   lcd.print("C");
 }
 