#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// Replace with your network credentials
const char *ssid = "ead.elhawary";
const char *password = "e15021979";

// Define pins for sensors
#define SOIL_PIN 35 // ESP32 pin GIOP36 (ADC0) that connects to AOUT pin of moisture sensor
#define GAS_PIN 34  // ESP32 pin GIOP34 (ADC6) that connects to AOUT pin of gas sensor
// Define pins for LEDs
#define LED_PIN 32     // ESP32 pin GIOP32 that connects to the positive pin of the LED
#define RED_LED_PIN 33 // ESP32 pin GIOP33 that connects to the positive pin of the red LED
// Initialize LEDs as outputs
// Define threshold value for soil moisture sensor
#define THRESHOLD 2000 // Adjust this value according to your calibration
// Define variables for temperature and humidity readings

// Create a web server object
WebServer server(80);

// Handle root url (/)
void handleRoot()
{
  // Read analog values from sensors
  int soilValue = analogRead(SOIL_PIN);
  int gasValue = analogRead(GAS_PIN);

  // Determine if the soil is wet or dry
  String soilStatus;
  if (soilValue > THRESHOLD)
  {
    soilStatus = "Dry";
  }
  else
  {
    soilStatus = "Wet";
  }
  // Initialize LEDs as outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  // Turn on or off LEDs based on gas status
  if (gasValue >= 58)
  {
    digitalWrite(LED_PIN, HIGH);    // Turn on LED
    digitalWrite(RED_LED_PIN, LOW); // Turn off red LED
  }
  else
  {
    digitalWrite(LED_PIN, LOW);      // Turn off LED
    digitalWrite(RED_LED_PIN, HIGH); // Turn on red LED
  }

  // Create a HTML web page
  String html = "<!DOCTYPE html><html>\n";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  html += "<style>body { font-family: Arial; text-align: center; margin: 0px; padding: 0px; }\n";
  html += ".container { width: 80%; margin: auto; }\n";
  html += ".sensor { font-size: 2rem; font-weight: bold; }\n";
  html += ".value { font-size: 3rem; color: green; }\n";
  html += ".status { font-size: 2rem; color: blue; }\n";

  html += "</style></head>\n";
  html += "<body><div class=\"container\">\n";
  html += "<h1>ESP32 Weather_Live </h1>\n";
  html += "<a href= https://r5nzumpc6j2o6nm7zqzszq.on.drv.tw/Weather-live/ >More Weather</a> \n";

  // Display soil moisture sensor data
  html += "<div class=\"sensor\">Soil Moisture</div>\n";
  html += "<div class=\"value\">" + String(soilValue) + "</div>\n";
  html += "<div class=\"status\">" + soilStatus + "</div>\n";

  // Display gas sensor data
  html += "<div class=\"sensor\">Carbon Dioxide</div>\n";
  html += "<div class=\"value\">" + String(gasValue) + "</div>\n";

  html += "</div></body></html>\n";

  // Send the HTML page to the client
  server.send(200, "text/html", html);
}

void setup()
{

  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);

  // Wait until connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address:Null ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Hello platformIO");
}

void loop()
{

  // Handle client requests
  server.handleClient();
  //Serial.println("Hello platformIO");
  //delay(1000);
}