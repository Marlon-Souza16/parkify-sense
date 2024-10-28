const int car_distance = 40;

// Entradas do Ultrassônico
const int TRIG = 3;
const int ECHO = 2;

// Pinos dos LEDs
const int ledGreen = 6;
const int ledRed = 8;

// Fotoresistor conectado ao pino A2
const int LDR_PIN = A2;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  pinMode(LDR_PIN, INPUT);
}

void loop() {
  int distance = sensor(TRIG, ECHO);
  int ldrValue = analogRead(LDR_PIN);

  if (distance <= car_distance && ldrValue >  650 ) {
    Serial.println("Warning: ");
    
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.print(" cm | Luminosidade: ");
    Serial.println(ldrValue);

    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
  } 
  else {
    
    Serial.println("Ok: ");
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.print(" cm | Luminosidade: ");
    Serial.println(ldrValue);
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
