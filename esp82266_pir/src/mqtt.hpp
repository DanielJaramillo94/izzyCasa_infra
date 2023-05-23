#include <PubSubClient.h>

const char* MQTT_BROKER_ADRESS = "*********";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP8266Client";
const char* MQTT_TOPIC_NAME = "pir/balcony";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void publishMessage(const char* topic, const char* message) {
  if(mqttClient.publish(topic, message)) {
    Serial.println("Message published successfully to topic '" + String(topic) + "' with message '" + String(message) + "'");
  } else {
    Serial.println("Error in message publishing to topic '" + String(topic) + "'");
}
}

void connect() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect(MQTT_CLIENT_NAME)) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe(MQTT_TOPIC_NAME);
    } else {
      Serial.println("Failed with state " + String(mqttClient.state()) + ", trying again in 2 seconds");
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