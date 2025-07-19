#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <MPU6050.h>

// GPS on pins 4 (TX), 3 (RX)
SoftwareSerial gpsSerial(4, 3); 
TinyGPSPlus gps;

// GSM on pins 7 (TX), 8 (RX)
SoftwareSerial gsmSerial(7, 8); 

MPU6050 mpu;

float ax, ay, az;
float gx, gy, gz;

const int pushButton = 2;
bool alertSent = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  pinMode(pushButton, INPUT_PULLUP);

  Serial.println("Initializing MPU6050...");
  mpu.initialize();
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected.");
  } else {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  delay(1000);
}

void loop() {
  if (digitalRead(pushButton) == LOW) {
    Serial.println("Manual termination triggered.");
    alertSent = false;  // Reset for testing
    delay(2000);
  }

  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  float totalAccel = sqrt(ax * ax + ay * ay + az * az) / 16384.0; // Normalize

  if (totalAccel > 2.5 && !alertSent) {  // Threshold, adjust as needed
    Serial.println("Possible accident detected!");
    sendAlert();
    alertSent = true;
  }

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  delay(1000);
}

void sendAlert() {
  String message = "Accident Detected!\n";

  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();

    message += "Location: https://maps.google.com/?q=";
    message += String(latitude, 6) + "," + String(longitude, 6);
  } else {
    message += "GPS location not available.";
  }

  Serial.println("Sending SMS...");
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+91xxxxxxxxxx\"");  // Replace with real number
  delay(1000);
  gsmSerial.print(message);
  gsmSerial.write(26); // ASCII code for Ctrl+Z
  Serial.println("Alert sent.");
}
