#include <ESP8266WiFi.h>
#include <Servo.h>

Servo myServo;  // Create a Servo object

int servoPin = D2;  // Define the pin connected to the servo motor

void setup() {
  myServo.attach(servoPin);  // Attach the servo on pin D2
}

void loop() {
  myServo.write(0);   // Move servo to 0 degrees
  delay(1000);        // Wait for 1 second
  
  myServo.write(90);  // Move servo to 90 degrees
  delay(1000);        // Wait for 1 second
  
  myServo.write(180); // Move servo to 180 degrees
  delay(1000);        // Wait for 1 second
}
