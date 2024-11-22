#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Servo.h>

Servo myServo;
 // Initialize DHT sensor on pin D4

// WiFi credentials
const char* ssid = "GUSTO_209";
const char* password = "Gusto@123";

// Pin assignments
#define LDR_PIN D7
#define TRIG_PIN D5
#define ECHO_PIN D6
#define LED_PIN D1

#define SERVO_PIN D3



float sensitivity = 0.185;

// Base API URL (set this dynamically if needed)
String baseUrl = "http://192.168.10.181:5000/api";

// API endpoints (constructed dynamically)
String ledStatusUrl = baseUrl + "/led/status";


String ultrasonicDataUrl = baseUrl + "/ultrasonic/distance";
String ldrDataUrl = baseUrl + "/ldr/light";
String servoControlUrl = baseUrl + "/servo/angle";
String ldrledAutomationUrl = baseUrl + "/ldrledautomation/status";



String ultrasonicledAutomationUrl = baseUrl + "/ultrasonicledautomation/status";

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
  pinMode(LED_PIN, OUTPUT); 
  pinMode(TRIG_PIN, OUTPUT); pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN); myServo.write(0);
  
  
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

void controlServo() {
  int angle = fetchData(servoControlUrl).toInt();
  if (angle >= 0 && angle <= 180) {
    myServo.write(angle);
    Serial.println("Servo moved to angle: " + String(angle));
  }
}





void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    bool ldrLedActive = fetchAutomationStatus(ldrledAutomationUrl);
    
    bool ultrasonicLedActive = fetchAutomationStatus(ultrasonicledAutomationUrl);

    

    controlDevice(ledStatusUrl, LED_PIN);
    
    controlServo();
    


    // Ultrasonic Sensor
    digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = microsecondsToCentimeters(duration);
    sendPostRequest(ultrasonicDataUrl, "{\"distance\":" + String(distance) + "}");

    // LDR Sensor
    int ldrValue = digitalRead(LDR_PIN);
    sendPostRequest(ldrDataUrl, "{\"lightIntensity\":" + String(ldrValue) + "}");

    // LDR + LED Automation
    if (ldrLedActive) {
      sendPostRequest(ledStatusUrl, ldrValue == 0 ? "{\"status\": \"OFF\"}" : "{\"status\": \"ON\"}");
    }

    // Ultrasonic + LED Automation
    if (ultrasonicLedActive) {
      sendPostRequest(ledStatusUrl, distance > 30 ? "{\"status\": \"OFF\"}" : "{\"status\": \"ON\"}");
    }





    delay(1000);
  }
}
