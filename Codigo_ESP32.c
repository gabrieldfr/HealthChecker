#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define OXIMETRO 34
#define HEARTBEATS 35

#define DHTTYPE DHT22
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE);

// MQTT defines
#define MQTT_BROKER "46.17.108.113"
#define MQTT_PORT 1883
#define MQTT_TOPIC_SUBSCRIBE "/TEF/Hosp108/cmd"
#define MQTT_TOPIC_PUBLISH "/TEF/Hosp108/attrs"
#define MQTT_TOPIC_PUBLISH_OXIMETRO "/TEF/Hosp108/attrs/o"
#define MQTT_TOPIC_PUBLISH_HEARTBEATS "/TEF/Hosp108/attrs/h"
#define MQTT_TOPIC_PUBLISH_TEMPERATURE "/TEF/Hosp108/attrs/t"
#define MQTT_CLIENT_ID "fiware_108"
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(OXIMETRO, INPUT);
  pinMode(HEARTBEATS, INPUT);
  initWiFi();
  initMQTT();
}


void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  publishSensorData();
  client.loop();
}


void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}


void initMQTT() {
  client.setServer(MQTT_BROKER, MQTT_PORT);
}


void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect(MQTT_CLIENT_ID)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(MQTT_TOPIC_SUBSCRIBE);
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      delay(5000);
    }
  }
}


void publishSensorData() {
  char msgBuffer[4];
  int Oximetro_Value = analogRead(34);
  // Serial.print(map(Oximetro_Value, 0, 1023, 0, 100));
  // Serial.println('%');
  int json_value = map(Oximetro_Value, 0, 4095, 0, 100);
  //Serial.println(json_value);
  sprintf(msgBuffer, "%d", json_value);
  client.publish(MQTT_TOPIC_PUBLISH_OXIMETRO, msgBuffer);

  int HeartBeats_Value = analogRead(35);
  json_value = map(HeartBeats_Value, 0, 4095, 60, 100);
  sprintf(msgBuffer, "%d", json_value);
  client.publish(MQTT_TOPIC_PUBLISH_HEARTBEATS, msgBuffer);

  float Temperature_Value = dht.readTemperature();
  dtostrf(Temperature_Value, 4, 1, msgBuffer);
  client.publish(MQTT_TOPIC_PUBLISH_TEMPERATURE, msgBuffer);
  delay(100);
}
