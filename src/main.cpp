#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "SensorReadings.h"
#include "WebPage.h"
#include <WiFiManager.h>

// Create a web server object
WebServer server(80);

SensorReadings readings;
WebPage page(&readings);

// Handle root url (/)
void handleRoot() {
  readings.updateStatus();
  server.send(200, "text/html", page.getHTML());
}

void setup() {
  Serial.begin(115200); 
    WiFiManager wm;

   
    bool res;
    res = wm.autoConnect("Weather-live","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected.... :)");
    }
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
