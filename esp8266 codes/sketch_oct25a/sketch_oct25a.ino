#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>
#include <Servo.h>

Servo myServo;

// WiFi credentials
const char* ssid = "MPT KTN";
const char* password = "09799839789";

// Sensor and device pins
#define DHTPIN D4  
#define DHTTYPE DHT11
#define LDR_PIN D7
#define TRIG_PIN D5
#define ECHO_PIN D6
#define LED_PIN D1
#define PIR_PIN D2
#define SERVO_PIN D3
#define CURRENT_PIN A0

float sensitivity = 0.185;

// DHT11 setup
DHT dht(DHTPIN, DHTTYPE);

// API URLs
const char* ledStatusUrl = "http://192.168.1.9:5000/api/led/status";
const char* dhtDataUrl = "http://192.168.1.9:5000/api/dht/dhtdata";
const char* pirDataUrl = "http://192.168.1.9:5000/api/pir/motion";
const char* ultrasonicDataUrl = "http://192.168.1.9:5000/api/ultrasonic/distance";
const char* ldrDataUrl = "http://192.168.1.9:5000/api/ldr/light";
const char* servoControlUrl = "http://192.168.1.9:5000/api/servo/angle";
const char* ldrledAutomationUrl = "http://192.168.1.9:5000/api/ldrledautomation/status";
const char* currentDataUrl = "http://192.168.1.9:5000/api/current/currentdata";

WiFiClient client;

// Helper functions
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

void sendPostRequest(const char* url, String postData) {
  HTTPClient http;
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  int httpCode = http.POST(postData);

  if (httpCode > 0) {
    Serial.println("Data sent successfully: " + postData);
  } else {
    Serial.println("Failed to send data: " + postData);
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
    myServo.write(0);
  dht.begin();

  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void controlLED() {
  HTTPClient httpLed;
  httpLed.begin(client, ledStatusUrl);
  int httpCode = httpLed.GET();
  if (httpCode == HTTP_CODE_OK) {
    String ledStatus = httpLed.getString();
    Serial.println("LED Status: " + ledStatus);
    digitalWrite(LED_PIN, ledStatus == "ON" ? HIGH : LOW);
  }
  httpLed.end();
}

void controlServo() {
  HTTPClient httpServo;
  httpServo.begin(client, servoControlUrl);
  int httpCode = httpServo.GET();
  if (httpCode == HTTP_CODE_OK) {
    String servoAngle = httpServo.getString();
    int angle = servoAngle.toInt(); // Convert string to int
    if (angle >= 0 && angle <= 180) { // Valid angle range for a servo motor
      myServo.write(angle); // Move servo to the angle
      Serial.println("Servo moved to angle: " + String(angle));
    }
  }
  httpServo.end();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    // Fetch automation status from the server
    bool isLdrLedAutomationActive = fetchLdrLedAutomationStatusFromServer();

    // DHT11 Data
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (!isnan(humidity) && !isnan(temperature)) {
      String dhtPostData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
      sendPostRequest(dhtDataUrl, dhtPostData);
    }

    controlLED();

    // PIR Sensor Data
    int motionDetected = digitalRead(PIR_PIN);
    Serial.println(motionDetected ? "Motion Detected!" : "No Motion");
    String pirPostData = "{\"motionDetected\":" + String(motionDetected) + "}";
    sendPostRequest(pirDataUrl, pirPostData);

    // Ultrasonic Data
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = microsecondsToCentimeters(duration);
    String ultrasonicPostData = "{\"distance\":" + String(distance) + "}";
    sendPostRequest(ultrasonicDataUrl, ultrasonicPostData);

    // LDR Data
    int ldrValue = digitalRead(LDR_PIN);
    String ldrPostData = "{\"lightIntensity\":" + String(ldrValue) + "}";
    sendPostRequest(ldrDataUrl, ldrPostData);


    // ldr led automation only works automation is on
    if (isLdrLedAutomationActive) {
    //LDR + LED Automation
    if (ldrValue == 0) {
      // If light is detected, turn off the LED
    sendLEDStatus("OFF");  // Update LED status to server
    }else if (ldrValue == 1){
    // If no light is detected, turn on the LED    
    sendLEDStatus("ON");  // Update LED status to server
    }
    }


    // Servo Control
    controlServo();

    //current sensor
    int currentsensorValue = analogRead(CURRENT_PIN);
  
    // Convert the analog value to voltage
    float voltage = currentsensorValue * (5.0 / 1024.0); // if using 5V reference
    float current = (voltage - 2.5) / sensitivity; // Offset voltage 2.5V
    String currentPostData = "{\"voltage\":" + String(voltage) + ",\"current\":" + String(current) + "}";
    sendPostRequest(currentDataUrl, currentPostData);
  
    Serial.print("Current: ");
    Serial.print(current);
    Serial.print(voltage);
    Serial.println(" A");
     
  }

  delay(1000);  // 5-second delay between loops
}

// Function to send LED status to the server
void sendLEDStatus(String status) {
  

    String postData = "{\"status\": \"" + status + "\"}";
    sendPostRequest(ledStatusUrl, postData);

  
}


bool fetchLdrLedAutomationStatusFromServer() {
  HTTPClient httpldrled;
  httpldrled.begin(client, ldrledAutomationUrl);
  int httpCode = httpldrled.GET();

  if (httpCode > 0) {
    String payload = httpldrled.getString();
    if (payload.indexOf("true") > -1) {
      return true;
    } else {
      return false;
    }
  }

  httpldrled.end();
  return true;  // Default to true if the request fails
}


