# Modificação feita para suportar ESP32.

const int  car_distance = 10;

// entradas do arduino hehe
const int TRIG = 3;
const int ECHO = 2;

const int ledGreen = 7;
const int ledRed = 8;

float seno;
float frequency;


void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop() {
  int distance = sensor(TRIG,ECHO);

  if (distance <= car_distance) {
    Serial.print(" Warning: ");
    Serial.print(" cm: ");
    Serial.print(distance);
    
    digitalWrite(legGreen, LOW);
    digitalWrite(ledRed, HIGH);
  }
  else {
     Serial.print("Ok: ");
     Serial.print(distance);
     Serial.println("cm");
    
     digitalWrite(ledGreen, HIGH);
     digitalWrite(ledRed, LOW);
  }

  delay(100);
}


int sensor(int pinotrig, int pinoecho) {
  digitalWrite(pinotrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig, LOW);

  return pulseIn(pinoecho ,HIGH)/58;
}