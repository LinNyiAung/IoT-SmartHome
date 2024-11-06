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

// DHT11 setup
DHT dht(DHTPIN, DHTTYPE);

// API URLs
const char* ledStatusUrl = "http://192.168.1.10:5000/api/led/status";
const char* dhtDataUrl = "http://192.168.1.10:5000/api/dht/dhtdata";
const char* pirDataUrl = "http://192.168.1.10:5000/api/pir/motion";
const char* ultrasonicDataUrl = "http://192.168.1.10:5000/api/ultrasonic/distance";
const char* ldrDataUrl = "http://192.168.1.10:5000/api/ldr/light";
const char* servoControlUrl = "http://192.168.1.10:5000/api/servo/angle";

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


    // Servo Control
    controlServo();
     
  }

  delay(1000);  // 5-second delay between loops
}
