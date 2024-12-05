#include <SoftwareSerial.h>

const int RX_PIN = 2;
const int TX_PIN = 3;
int is_avaliable = 1;
String Spot = "C15";

SoftwareSerial espSerial(RX_PIN, TX_PIN);

const int car_distance = 40;

const int TRIG = 12;
const int ECHO = 13;

const int ledGreen = 6;
const int ledRed = 8;

const int LDR_PIN = A2;

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int distance = sensor(TRIG, ECHO);
  int ldrValue = analogRead(LDR_PIN);

  if (distance <= car_distance && ldrValue > 600) {
    is_avaliable = 0;
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    is_avaliable = 1;
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  String mensagem = "Luminosidade: " + String(ldrValue) + 
                    " | Distancia: " + String(distance) + 
                    " | Is_avaliable: " + String(is_avaliable) + 
                    " | Vaga: " + Spot;

  Serial.println(mensagem);
  espSerial.println(mensagem);

  delay(2000);
}

int sensor(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);

  return pulseIn(pinoecho, HIGH) / 58;
}
