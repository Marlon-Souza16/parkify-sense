#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Marlon";
const char* password = "batata123";

const char* serverName = "http://192.168.142.171:8000/dados";

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi!");
  Serial.println("ESP32 pronto para enviar dados!");
  Serial.println(WiFi.localIP());
}


void checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconectando ao Wi-Fi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("Reconectado!");
  }
}

void loop() {
  checkWiFiConnection();

  if (Serial.available()) {
    String dado = Serial.readStringUntil('\n');
    Serial.println("Recebido do Arduino: " + dado);

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      http.begin(serverName);


      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "dado=" + dado;

      int httpResponseCode = http.POST(httpRequestData);

      if (httpResponseCode > 0) {
        String resposta = http.getString();
        Serial.println("Código de resposta HTTP: " + String(httpResponseCode));
        Serial.println("Resposta do servidor: " + resposta);
      } else {
        Serial.println("Erro ao enviar POST: " + String(httpResponseCode));
      }

      http.end();
    } else {
      Serial.println("Wi-Fi Desconectado");
    }
  }
  delay(100);
}
