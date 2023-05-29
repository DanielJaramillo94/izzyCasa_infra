extern const int LED_ROOM_0;
extern const int LED_ROOM_1;
extern const int LED_ROOM_2;
extern PubSubClient mqttClient;

extern const char* MQTT_TOPIC_LIGHTS_ROOM_0;
extern const char* MQTT_TOPIC_LIGHTS_ROOM_1;
extern const char* MQTT_TOPIC_LIGHTS_ROOM_2;

void handleMessage(int led_room, String message) {
  if (message.equals("1")) {
    digitalWrite(led_room, HIGH);
  } else if(message.equals("0")) {
    digitalWrite(led_room, LOW);
  }
}

void handleEvent(String topic, String message) {
  if (topic.equals(MQTT_TOPIC_LIGHTS_ROOM_0)) {
    handleMessage(LED_ROOM_0, message);
  }
  if (topic.equals(MQTT_TOPIC_LIGHTS_ROOM_1)) {
    handleMessage(LED_ROOM_1, message);
  }
  if (topic.equals(MQTT_TOPIC_LIGHTS_ROOM_2)) {
    handleMessage(LED_ROOM_2, message);
  }
}
