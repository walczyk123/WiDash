#ifndef ROUTES_H
#define ROUTES_H

#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include "html_index.h"
#include "html_sensors.h"
#include "html_networks.h"
#include "html_status.h"
#include "json_sensors.h"

// Forward declarations
using HtmlCallback = void (*)(const char* html_template);
using JsonCallback = void (*)(const String& json);

// Route definitions
inline void setupRoutes(
  ESP8266WebServer& server,
  NTPClient& timeClient,
  HtmlCallback serveHTML_P,
  JsonCallback serveJSON
) {
  server.on("/", [&]() {
    serveHTML_P(HTML_INDEX);
  });

  server.on("/sensors", [&]() {
    serveHTML_P(HTML_SENSORS);
  });

  server.on("/networks", [&]() {
    serveHTML_P(HTML_NETWORKS);
  });

  server.on("/status", [&]() {
    serveHTML_P(HTML_STATUS);
  });

  server.on("/sensors.json", [&]() {
    serveJSON(generateSensorsJson(timeClient));
  });
}

#endif
