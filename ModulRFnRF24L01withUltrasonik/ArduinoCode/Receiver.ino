#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(9,10); // CE, CSN

const byte address[6] = "00001";
const int triggerDistance1= 10;
const int triggerDistance2= 6;
const int triggerDistance3= 3;
const int triggerDistance4= 14;

const int ledPin_1 = 7;
const int ledPin_2 = 6;
const int ledPin_3 = 5;
const int ledPin_4 = 4;



void setup() {
  Serial.begin(9600);
  radio.begin();
  pinMode(ledPin_1,OUTPUT);
  pinMode(ledPin_2,OUTPUT);
  pinMode(ledPin_3,OUTPUT);
  pinMode(ledPin_4,OUTPUT);
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
  if (radio.available()) {
    int ukur[32];
    radio.read(ukur, 32);
    int distance = ukur[0];

    Serial.println(distance);

    if(distance == triggerDistance1){
      digitalWrite(ledPin_1, HIGH);
    }else{
      digitalWrite(ledPin_1, LOW);
    }
if(distance == triggerDistance2){
      digitalWrite(ledPin_2, HIGH);
    }else{
      digitalWrite(ledPin_2, LOW);
    }
    if(distance == triggerDistance3){
      digitalWrite(ledPin_3, HIGH);
    }else{
      digitalWrite(ledPin_3, LOW);
    }
    if(distance <= triggerDistance4){
      digitalWrite(ledPin_1, HIGH);
      digitalWrite(ledPin_2, HIGH);
      digitalWrite(ledPin_3, HIGH);
      digitalWrite(ledPin_4, HIGH);
    }else{
      digitalWrite(ledPin_1, LOW);
      digitalWrite(ledPin_2, LOW);
      digitalWrite(ledPin_3, LOW);
      digitalWrite(ledPin_4, LOW);
    }
  }
}