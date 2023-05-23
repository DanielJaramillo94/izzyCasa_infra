#include <PubSubClient.h>

const char* MQTT_BROKER_ADRESS = "*********";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP8266Client";
const char* MQTT_TOPIC_NAME = "home";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void publishMessage(const char* topic, const char* message) {
  mqttClient.publish(topic, message);
  Serial.print("Message published to topic: ");
  Serial.println(topic);
}

void connect() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");

    if (mqttClient.connect(MQTT_CLIENT_NAME)) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe(MQTT_TOPIC_NAME);
    } else {
      Serial.print("Failed with state ");
      Serial.print(mqttClient.state());
      delay(2000);
    }
  }
}

void InitMqtt() {
   mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
   connect();
}

void handleMqtt(){
  if (!mqttClient.connected()) {
    connect();
  }
  mqttClient.loop();
}