#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Servo.h>

Servo myServo;
DHT dht(D4, DHT11);  // Initialize DHT sensor on pin D4

// WiFi credentials
const char* ssid = "GUSTO WiFi";
const char* password = "Gusto@123";

// Pin assignments


#define LED_PIN D1



#define RELAY_PIN D8

float sensitivity = 0.185;

// Base API URL (set this dynamically if needed)
String baseUrl = "http://192.168.20.31:5000/api";

// API endpoints (constructed dynamically)
String ledStatusUrl = baseUrl + "/led/status";
String dhtDataUrl = baseUrl + "/dht/dhtdata";




String ldrledAutomationUrl = baseUrl + "/ldrledautomation/status";

String bldcfanStatusUrl = baseUrl + "/bldcfan/bldcfanstatus";
String dhtfanAutomationUrl = baseUrl + "/dhtfanautomation/status";


WiFiClient client;

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void sendPostRequest(String url, String postData) {
  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(postData);
  Serial.println(httpCode > 0 ? "Data sent: " + postData : "Failed to send: " + postData);
  http.end();
}

String fetchData(String url) {
  HTTPClient http;
  http.begin(client, url);
  int httpCode = http.GET();
  String payload = (httpCode == HTTP_CODE_OK) ? http.getString() : "";
  http.end();
  return payload;
}

bool fetchAutomationStatus(String url) {
  return fetchData(url).indexOf("true") > -1;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); pinMode(RELAY_PIN, OUTPUT); 
  
  
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void controlDevice(String url, uint8_t pin) {
  digitalWrite(pin, fetchData(url) == "ON" ? HIGH : LOW);
}



void sendSensorData() {
  float humidity = dht.readHumidity(), temperature = dht.readTemperature();
  if (!isnan(humidity) && !isnan(temperature)) {
    sendPostRequest(dhtDataUrl, "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}");
  }
}

void controlFanAutomation(float temperature) {
  if (fetchAutomationStatus(dhtfanAutomationUrl)) {
    String fanStatus = (temperature > 35) ? "ON" : "OFF";
    sendPostRequest(bldcfanStatusUrl, "{\"status\": \"" + fanStatus + "\"}");
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    bool ldrLedActive = fetchAutomationStatus(ldrledAutomationUrl);
    bool dhtFanActive = fetchAutomationStatus(dhtfanAutomationUrl);
    

    // DHT Sensor
    sendSensorData();

    controlDevice(ledStatusUrl, LED_PIN);
    controlDevice(bldcfanStatusUrl, RELAY_PIN);
    
    
    

    

    

    // LDR + LED Automation
    // if (ldrLedActive) {
    //   sendPostRequest(ledStatusUrl, ldrValue == 0 ? "{\"status\": \"OFF\"}" : "{\"status\": \"ON\"}");
    // }

    

    // DHT + Fan Automation
    controlFanAutomation(dht.readTemperature());

    

    delay(1000);
  }
}
