#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>


// 1. CONFIGURAÇÕES DE WI-FI
const char* rede     = "NOME_REDE_WIFI"; 
const char* senha = "SENHA_WIFI"; 

// 2. CONFIGURAÇÕES UBIDOTS (Gráficos)
const char* servidor_ubi = "industrial.api.ubidots.com";
const char* token_ubi  = "TOKEN"; // <--- COLE SEU TOKEN
const char* nome_ubi  = "monitor-ac"; // Nome do device no Ubidots

WiFiClient mqtt_ubi; // Primeira conexão MQTT
PubSubClient cliente_ubi(mqtt_ubi); // Cliente MQTT Ubidots

// 3. CONFIGURAÇÕES HIVEMQ (Tempo Real)
const char* servidor_hive = "broker.hivemq.com";
const char* topico_hive  = "ufes/pic/monitor-ac"; // Tópico para ver no site

WiFiClient mqtt_hive; // Segunda conexão MQTT
PubSubClient cliente_hive(mqtt_hive); // Cliente MQTT HiveMQ


// 4. HARDWARE (PZEM v1.0)
PZEM004Tv30 pzem(Serial2, 16, 17); // portas RX e TX do ESP32
#define LED_STATUS 2

unsigned long ultimo_millis = 0;


// 5. FUNÇÕES DE CONEXÃO: Wi-Fi e MQTTs

void setup_wifi() {
  Serial.print("\nConectando Wi-Fi: "); 
  Serial.println(rede);
  WiFi.begin(rede, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); 
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
}

void reconecta_ubidots() {
  if (!cliente_ubi.connected()) {
    Serial.print("Conectando Ubidots... ");
    String id_cliente = "ESP32_UBI_" + String(random(0xffff), HEX); // configura um ID aleatório, para não ter conflito
    if (cliente_ubi.connect(id_cliente.c_str(), token_ubi, "")) {
      Serial.println("OK!");
    } else {
      Serial.print("Falha Ubidots rc="); 
      Serial.println(cliente_ubi.state());
    }
  }
}

void reconecta_hiveMQ() {
  if (!cliente_hive.connected()) {
    Serial.print("Conectando HiveMQ... ");
    String id_cliente = "ESP32_HIVE_" + String(random(0xffff), HEX);
    if (cliente_hive.connect(id_cliente.c_str())) {
      Serial.println("OK!");
    } else {
      Serial.print("Falha HiveMQ rc="); 
      Serial.println(cliente_hive.state());
    }
  }
}

// 6. LEITURA DOS DADOS E ENVIO POR MQTT

void ler_e_enviar() {
  digitalWrite(LED_STATUS, HIGH);

  // Lê os dados do sensor
  float tensao = pzem.voltage();
  float corrente = pzem.current();
  float potencia = pzem.power();
  float energia = pzem.energy();
  float fator_potencia = pzem.pf();

  if (isnan(tensao)) {
      Serial.println("Erro leitura PZEM!"); // Caso ocorra uma falha com o sensor
      digitalWrite(LED_STATUS, LOW);
      return;
  }

  Serial.printf("Lido: %.1fV | %.2fA | %.1fW | %.3fkWh | %.2f\n", tensao, corrente, potencia, energia, fator_potencia);

  // Envio ao Ubidots (formato json)
  json_ubi += "\"tensao\":" + String(tensao, 1) + ",";
  json_ubi += "\"corrente\":" + String(corrente, 2) + ",";
  json_ubi += "\"potencia\":" + String(potencia, 1) + ",";
  json_ubi += "\"energia\":" + String(energia, 3) + ",";
  json_ubi += "\"fator de potencia\":" + String(fator_potencia, 2);
  json_ubi += "}";
  
  String topico_ubi = "/v1.6/devices/" + String(nome_ubi); // formato de tópico exigido pela plataforma
  cliente_ubi.publish(topico_ubi.c_str(), json_ubi.c_str());

  // Envio ao HiveMQ (formato legível)
  String pacote_hive = "Monitor AC: ";
  pacote_hive += "Tensao: " + String(tensao, 1) + "V | ";
  pacote_hive += "Corrente: " + String(corrente, 2) + "A | ";
  pacote_hive += "Potencia: " + String(potencia, 1) + "W | ";
  pacote_hive += "Energia: " + String(energia, 3) + "kWh | ";
  pacote_hive += "Fator de potencia: " + String(fator_potencia, 2);
  
  cliente_hive.publish(topico_hive, pacote_hive.c_str());

  digitalWrite(LED_STATUS, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_STATUS, OUTPUT);
  setup_wifi();
  
  // Configura os dois servidores
  cliente_ubi.setServer(servidor_ubi, 1883);
  cliente_hive.setServer(servidor_hive, 1883);
}

void loop() {
  // Garante que os dois estejam conectados
  if (!cliente_ubi.connected()) 
    reconecta_ubidots();
  if (!cliente_hive.connected()) 
    reconecta_hiveMQ();
  
  // Mantém as conexões vivas
  cliente_ubi.loop();
  cliente_hive.loop();

  if (millis() - ultimo_millis > 5000) {
    ultimo_millis = millis();
    ler_e_enviar();
  }
}