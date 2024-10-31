#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

const char* ssid = "MPT KTN";
const char* password = "09799839789";

#define DHTPIN D4  // DHT11 connected to GPIO2 (D4 on NodeMCU)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define LDR_PIN D7

#define TRIG_PIN D5
#define ECHO_PIN D6

long duration;
int distance;

const char* ledStatusUrl = "http://192.168.1.10:5000/api/led/status";
const char* dhtDataUrl = "http://192.168.1.10:5000/api/dht/dhtdata";
const char* pirDataUrl = "http://192.168.1.10:5000/api/pir/motion";
const char* ultrasonicDataUrl = "http://192.168.1.10:5000/api/ultrasonic/distance";
const char* ldrDataUrl = "http://192.168.1.10:5000/api/ldr/light";

WiFiClient client;
#define LED_PIN D1
#define PIR_PIN D2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Send DHT11 data
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    if (!isnan(humidity) && !isnan(temperature)) {
      HTTPClient http;
      http.begin(client, dhtDataUrl);
      http.addHeader("Content-Type", "application/json");
      
      String postData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
      Serial.print(postData);
      int httpCode = http.POST(postData);
      
      if (httpCode > 0) {
        Serial.println("DHT data sent successfully");
      } else {
        Serial.println("Failed to send DHT data");
      }
      http.end();
    }

    // Check LED status
    HTTPClient http;
    http.begin(client, ledStatusUrl);
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


    // Send PIR sensor data
    int motionDetected = digitalRead(PIR_PIN);
    if (motionDetected == HIGH) {
    // Motion detected, turn on the LED
    Serial.println("Motion Detected!");
     
  } else {
    // No motion, turn off the LED
    Serial.println("No Motion");
  
  }
    http.begin(client, pirDataUrl);
    http.addHeader("Content-Type", "application/json");

    String pirPostData = "{\"motionDetected\":" + String(motionDetected == HIGH) + "}";
    Serial.println(pirPostData);
    http.POST(pirPostData);
    if (httpCode > 0) {
        Serial.println("PIR data sent successfully");
      } else {
        Serial.println("Failed to send PIR data");
      }
    http.end();

  // Send ultrasonic data
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = microsecondsToCentimeters(duration);

  
  http.begin(client, ultrasonicDataUrl);
  http.addHeader("Content-Type", "application/json");
  
  String postData = "{\"distance\":" + String(distance) + "}";
  Serial.println(postData);
  http.POST(postData);
  if (httpCode > 0) {
    Serial.println("Ultrasonic data sent successfully");
  } else {
    Serial.println("Failed to send ultrasonic data");
  }
  http.end();


  // Reading LDR sensor data
    int ldrValue = digitalRead(LDR_PIN);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Sending LDR data
    
    http.begin(client, ldrDataUrl);
    http.addHeader("Content-Type", "application/json");

    String ldrPostData = "{\"lightIntensity\":" + String(ldrValue) + "}";
    Serial.println(ldrPostData);
    http.POST(ldrPostData);

    if (httpCode > 0) {
      Serial.println("LDR data sent successfully");
    } else {
      Serial.println("Failed to send LDR data");
    }
    http.end();
  }
  delay(5000);  // 5-second delay between loops
}


long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}