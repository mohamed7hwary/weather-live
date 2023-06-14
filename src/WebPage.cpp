#include "WebPage.h"

WebPage::WebPage(SensorReadings* readings) {
  this->readings = readings;
}

String WebPage::getHTML() {
  String html = "<!DOCTYPE html><html>\n";
  //... omitting the rest of the HTML string for brevity

  html += "<div class=\"value\">" + String(readings->getSoilValue()) + "</div>\n";
  html += "<div class=\"status\">" + readings->getSoilStatus() + "</div>\n";
  html += "<div class=\"value\">" + String(readings->getGasValue()) + "</div>\n";

  html += "</div></body></html>\n";
  return html;
}
