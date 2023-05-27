#include <PubSubClient.h>

//const char* MQTT_BROKER_ADRESS = "*********";
const char* MQTT_BROKER_ADRESS = "192.168.1.5";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP32LivingRoom";
const char* MQTT_TOPIC_PIR = "pir/balcony";
const char* MQTT_TOPIC_SERVO = "servo/mainDoor";

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
      mqttClient.subscribe(MQTT_TOPIC_PIR);
      mqttClient.subscribe(MQTT_TOPIC_SERVO);
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

  Serial.println(topic);
  Serial.println("Mensaje de topico");
  String topicString = topic;
  if(topicString.equals("servo/mainDoor")){
    if(content.equals("1")){
      servo.write(90);
    }else if(content.equals("0")){
      servo.write(0);
    }    
  } else if(topicString.equals("pir/balcony") && content.equals("1")){
    startBlink(1);
  }
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



