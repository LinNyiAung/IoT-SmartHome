#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MPT KTN";
const char* password = "09799839789";
const char* serverUrl = "http://192.168.1.2:5000/api/led/status"; // Replace with server IP

WiFiClient client;  // Create a WiFiClient instance
#define LED_PIN D1  // LED pin

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, serverUrl);  // Pass WiFiClient instance and server URL

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println("LED Status: " + payload);

      if (payload == "ON") {
        digitalWrite(LED_PIN, HIGH);
      } else if (payload == "OFF") {
        digitalWrite(LED_PIN, LOW);
      }
    }
    http.end();
  }
  delay(5000);  // Check every 5 seconds
}
