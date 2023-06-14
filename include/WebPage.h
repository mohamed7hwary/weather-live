#ifndef WebPage_h
#define WebPage_h

#include <Arduino.h>
#include "SensorReadings.h"

class WebPage {
  public:
    WebPage(SensorReadings* readings);
    String getHTML();

  private:
    SensorReadings* readings;
};

#endif
