#include <SoftwareSerial.h>

// Defina os pinos para o SoftwareSerial
const int RX_PIN = 2; // Recebe dados do ESP32 (não usado neste caso)
const int TX_PIN = 3; // Envia dados para o ESP32

SoftwareSerial espSerial(RX_PIN, TX_PIN); // RX, TX

const int car_distance = 40;  // Distância mínima

// Entradas do Ultrassônico
const int TRIG = 4;
const int ECHO = 5;

// Pinos dos LEDs
const int ledGreen = 6;
const int ledRed = 8;

// Fotoresistor conectado ao pino A2
const int LDR_PIN = A2;

void setup() {
  Serial.begin(9600);      // Inicializa a comunicação serial com o PC
  espSerial.begin(9600);   // Inicializa a comunicação serial com o ESP32

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  pinMode(LDR_PIN, INPUT);  // Fotoresistor como entrada

  Serial.println("Iniciando o sistema...");
}

void loop() {
  int distance = sensor(TRIG, ECHO);  // Lê a distância
  int ldrValue = analogRead(LDR_PIN);  // Lê o valor do fotoresistor

  // Verifica se a distância está abaixo do limite e se a luminosidade está acima do limiar
  if (distance <= car_distance && ldrValue > 650 ) {
    String mensagem = "Warning: Distancia: " + String(distance) + " cm | Luminosidade: " + String(ldrValue);
    Serial.println(mensagem);        // Imprime no Monitor Serial
    espSerial.println(mensagem);     // Envia para o ESP32

    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  } 
  else {
    String mensagem = "Ok: Distancia: " + String(distance) + " cm | Luminosidade: " + String(ldrValue);
    Serial.println(mensagem);        // Imprime no Monitor Serial
    espSerial.println(mensagem);     // Envia para o ESP32

    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  delay(500);
}

int sensor(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);

  return pulseIn(pinoecho, HIGH) / 58;
}
