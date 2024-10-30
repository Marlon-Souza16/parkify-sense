#include <WiFi.h>
#include <HTTPClient.h>

// Credenciais da rede Wi-Fi
const char* ssid = "Marlon";
const char* password = "batata123";

// Endereço do servidor (substitua pelo IP do seu computador e porta correta)
const char* serverName = "http://192.168.142.171:8000/dados"; 

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  // Conexão Wi-Fi inicial
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi!");
  Serial.println("ESP32 pronto para receber dados!");
  Serial.println(WiFi.localIP());
}

// Função para verificar e reconectar ao Wi-Fi, se necessário
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
  // Verifica e reconecta ao Wi-Fi se necessário
  checkWiFiConnection();

  if (Serial1.available()) {  // Verifica se há dados recebidos do Arduino
    String dado = Serial1.readStringUntil('\n');  // Lê a mensagem
    Serial.println("Recebido do Arduino: " + dado);  // Exibe no monitor serial

    // Envia os dados pela internet via Wi-Fi
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      http.begin(serverName);  // Especifica o URL do servidor

      // Dados a serem enviados na requisição HTTP POST
      String httpRequestData = "dado=" + dado;

      int httpResponseCode = http.POST(httpRequestData);  // Envia a requisição POST

      if (httpResponseCode > 0) {
        String resposta = http.getString();  // Obtém a resposta do servidor
        Serial.println("Código de resposta HTTP: " + String(httpResponseCode));
        Serial.println("Resposta do servidor: " + resposta);
      } else {
        Serial.println("Erro ao enviar POST: " + String(httpResponseCode));
      }

      http.end();  // Libera recursos
    } else {
      Serial.println("Wi-Fi Desconectado");
    }
  }
  delay(10);  // Evita travamento do loop
}
