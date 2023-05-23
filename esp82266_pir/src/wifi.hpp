#include "ESP8266WiFi.h"

const char *ssid = "*********";
const char *password = "*********";
const char *hostname = "danis";

void ConnectWiFi_STA() {
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) { 
     digitalWrite(led, HIGH);
     delay(50);  
     digitalWrite(led, LOW);
     delay(50);  
     digitalWrite(led, HIGH);
     Serial.print('.'); 
   }
 
   Serial.println("");
   Serial.print("Starting STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
}