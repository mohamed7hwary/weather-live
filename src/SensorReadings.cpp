#include "Arduino.h"
#include "SensorReadings.h"
#include <ArduinoJson.h>

SensorReadings::SensorReadings() {
  pinMode(SOIL_PIN, INPUT);
  pinMode(GAS_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
}

void SensorReadings::readSensors() {
  soilValue = analogRead(SOIL_PIN);
  gasValue = analogRead(GAS_PIN);
}

void SensorReadings::updateStatus() {
  readSensors();

  if (soilValue > THRESHOLD) {
    soilStatus = "Dry";
  } else {
    soilStatus = "Wet";
  }

  updateLEDs();
}

void SensorReadings::updateLEDs() {
  if (gasValue >= 58) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }
}

int SensorReadings::getSoilValue() {
  return soilValue;
}

int SensorReadings::getGasValue() {
  return gasValue;
}

String SensorReadings::getSoilStatus() {
  return soilStatus;
}

String SensorReadings::getSoilDataAsJson() {
    StaticJsonDocument<100> doc;
    doc["value"] = getSoilValue();
    doc["status"] = getSoilStatus();
    String json;
    serializeJson(doc, json);
    return json;
}

String SensorReadings::getGasDataAsJson() {
    StaticJsonDocument<100> doc;
    doc["value"] = getGasValue();
    String json;
    serializeJson(doc, json);
    return json;
}