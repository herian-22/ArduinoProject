#include <SPI.h>

#include <nRF24L01.h>

#include <RF24.h>

const int trigPin = 2;
const int echoPin = 3;
long duration;
int distanceCm, distanceInch;

RF24 radio(9, 10); // CE, CSN

int ukur[1];

const byte address[6] = "00001";

void setup() {
  radio.begin();
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

  ukur[0] = distanceCm;
  radio.write(ukur, 1);
  delay(1000);  
  
}