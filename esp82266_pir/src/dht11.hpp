#include "DHT.h"

#define DHTPIN 12 
#define DHTTYPE DHT11

extern const int SECONDS_IN_MILLIS;
const char* MQTT_TOPIC_TEMPERATURE = "temperature/livingroom";

int lastTemperatureMeasure = millis();

DHT dht(DHTPIN, DHTTYPE);

void DTHsetup() {
  dht.begin();
}

void readDHT() {
  // float h = dht.readHumidity();
  float floatTemp = dht.readTemperature();
   
  if (isnan(floatTemp)) {
    Serial.println("Error reading the sensor");
    return;
  }
  
  int temp = (int)floatTemp;
  String messageToPublish = String(temp);
  publishMessage(MQTT_TOPIC_TEMPERATURE, messageToPublish.c_str());
  startBlink(4);
  Serial.println("Temperature: " + String(temp) + F("°C"));
}

void DTHloop(unsigned long now) {
  if (now - lastTemperatureMeasure > SECONDS_IN_MILLIS * 10) {
    lastTemperatureMeasure = now;
    Serial.println(String(now));
    readDHT();
  }
}