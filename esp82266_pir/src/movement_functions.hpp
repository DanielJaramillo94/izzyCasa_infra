void IRAM_ATTR detectsMovement() {
  publishMessage(MQTT_TOPIC_NAME, "1");
  startBlink(2);
}