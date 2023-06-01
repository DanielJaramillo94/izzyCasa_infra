#include <PubSubClient.h>

extern void startBlink(int blinks);
extern const int LED_ROOM_0;
extern const int LED_ROOM_1;
extern const int LED_ROOM_2;

//const char* MQTT_BROKER_ADRESS = "*********";
const char* MQTT_BROKER_ADRESS = "192.168.1.2";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP32Rooms";
const char* MQTT_TOPIC_LIGHTS_ROOM_0 = "lights/room0";
const char* MQTT_TOPIC_LIGHTS_ROOM_1 = "lights/room1";
const char* MQTT_TOPIC_LIGHTS_ROOM_2 = "lights/room2";
const char* MQTT_TOPIC_LIGHTS_ROOM_3 = "lights/room3";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

#include "mqtt_events_handler.hpp"

extern void handleEvent(String topic, String message);

void publishMessage(const char* topic, const char* message) {
  if(mqttClient.publish(topic, message)) {
    Serial.println("Message published successfully to topic '" + String(topic) + "' with message '" + String(message) + "'");
  } else {
    Serial.println("Error in message publishing to topic '" + String(topic) + "'");
  }
}

void suscribe() {
  mqttClient.subscribe(MQTT_TOPIC_LIGHTS_ROOM_0);
  mqttClient.subscribe(MQTT_TOPIC_LIGHTS_ROOM_1);
  mqttClient.subscribe(MQTT_TOPIC_LIGHTS_ROOM_2);
  mqttClient.subscribe(MQTT_TOPIC_LIGHTS_ROOM_3);
}

void connect() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect(MQTT_CLIENT_NAME)) {
      Serial.println("Connected to MQTT broker");
      suscribe();
    } else {
      Serial.println("Failed with state " + String(mqttClient.state()) + ", trying again in 2 seconds");
      delay(2000);
    }
  }
}

void OnMqttReceived(char* topic, byte* payload, unsigned int length) {

  String content = "";

  for (size_t i = 0; i < length; i++) {
    content.concat((char)payload[i]);
  }

  Serial.println("Message '" + String(content) + "' received from topic '" + String(topic) + "'");
  startBlink(1);
  handleEvent(String(topic), String(content));
}

void InitMqtt() {
  mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
  mqttClient.setCallback(OnMqttReceived);
  connect();
}

void handleMqtt(){
  if (!mqttClient.connected()) {
    connect();
  }
  mqttClient.loop();
}
