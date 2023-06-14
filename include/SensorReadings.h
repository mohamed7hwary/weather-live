#ifndef SensorReadings_h
#define SensorReadings_h

#include <Arduino.h>

#define SOIL_PIN 35 
#define GAS_PIN 34  
#define LED_PIN 32     
#define RED_LED_PIN 33 
#define THRESHOLD 2000 

class SensorReadings {
  public:
    SensorReadings();
    void updateStatus();
    int getSoilValue();
    int getGasValue();
    String getSoilStatus();

  private:
    int soilValue;
    int gasValue;
    String soilStatus;
    void readSensors();
    void updateLEDs();
};

#endif
