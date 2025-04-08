#ifndef ROUTES_H
#define ROUTES_H

#include <ESP8266WebServer.h>
#include "html_index.h"
#include "html_sensors.h"
#include "html_networks.h"
#include "html_status.h"

// Forward declaration of function defined in your main file
void serveHTML_P(const char* html_template);

// Route definitions
inline void setupRoutes(ESP8266WebServer& server) {
  server.on("/", []() {
    serveHTML_P(HTML_INDEX);
  });

  server.on("/sensors", []() {
    serveHTML_P(HTML_SENSORS);
  });

  server.on("/networks", []() {
    serveHTML_P(HTML_NETWORKS);
  });

  server.on("/status", []() {
    serveHTML_P(HTML_STATUS);
  });
}

#endif
