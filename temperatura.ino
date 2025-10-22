#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_AHTX0.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WebServer server(80);

Adafruit_AHTX0 aht;
Adafruit_Sensor *aht_humidity, *aht_temp;

void handleRoot() {
 // Get sensor readings
 sensors_event_t humidity;
 sensors_event_t temp;
 aht_humidity->getEvent(&humidity);
 aht_temp->getEvent(&temp);

 // Create HTML page with sensor data
 String html = "<html><body>";
 html += "<h1>Humidity and Temperature Sensor Data</h1>";
 html += "<p>Temperature: " + String(temp.temperature) + " deg C</p>";
 html += "<p>Humidity: " + String(humidity.relative_humidity) + " % rH</p>";
 html += "</body></html>";

 server.send(200, "text/html", html);
}

void setup() {
 Serial.begin(115200);
 delay(1000);

 // Connect to WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi...");
 }

 Serial.println("Connected to WiFi");

 // Initialize AHT sensor
 if (!aht.begin()) {
  Serial.println("Failed to find AHT10/AHT20 chip");
  while (1) {
   delay(10);
  }
 }

 Serial.println("AHT10/AHT20 Found!");
 aht_temp = aht.getTemperatureSensor();
 aht_temp->printSensorDetails();

 aht_humidity = aht.getHumiditySensor();
 aht_humidity->printSensorDetails();

 // Start web server
 server.on("/", handleRoot);
 server.begin();
 Serial.println("Web server started");
}

void loop() {
 server.handleClient();
}