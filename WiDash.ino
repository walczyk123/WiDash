#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "routes.h"

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

const int wifiRetries = 3;  // Number of WiFi connection attempts
const int RSSI_MIN = -100;  // Minimum signal level in dBm
const int RSSI_MAX = -50;   // Maximum signal level in dBm

int rssiToPercentage(int rssi) {
  if (rssi <= RSSI_MIN) return 0;
  if (rssi >= RSSI_MAX) return 100;
  return map(rssi, RSSI_MIN, RSSI_MAX, 0, 100);
}

int getSignalStrengthPercentage() {
  return rssiToPercentage(WiFi.RSSI());
}

int getSignalStrengthPercentage(int networkIndex) {
  return rssiToPercentage(WiFi.RSSI(networkIndex));
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== WiDash Boot ===");

  // Set WiFi to Station mode and connect
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_default, pass_default);
  Serial.print("Connecting to WiFi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries++ < wifiRetries) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" ✅ Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println(" ❌ Failed to connect.");
  }

  // Initialize NTP client
  timeClient.begin();

  // Setup web server routes
  setupRoutes();

  server.begin();
  Serial.println("HTTP server started.");

  // Show menu
  showSerialMenu();
}

void loop() {
  server.handleClient();
  timeClient.update();

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "1") {
      connectToWiFi();
    } else if (command == "2") {
      listAvailableNetworks();
    } else if (command == "3") {
      connectToNewWiFi();
    } else if (command == "4") {
      showConnectionStatus();
    } else if (command == "5") {
      disconnectFromWiFi();
    } else if (command == "exit") {
      Serial.println("Exiting and restarting...");
      delay(1000);
      ESP.restart();
    } else {
      Serial.println("Unknown command. Try again.");
    }

    showSerialMenu();
  }
}

void showSerialMenu() {
  Serial.println("\n=== MENU ===");
  Serial.println("1. Connect to saved network");
  Serial.println("2. List available networks");
  Serial.println("3. Connect to a new network");
  Serial.println("4. Show connection status");
  Serial.println("5. Disconnect from WiFi");
  Serial.println("exit. Restart device");
  Serial.print("Select option: ");
}

void connectToWiFi() {
  WiFi.begin(ssid_default, pass_default);
  Serial.print("Connecting to WiFi...");
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries++ < wifiRetries) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" ✅ Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println(" ❌ Connection failed.");
  }
}

void listAvailableNetworks() {
  int n = WiFi.scanNetworks();
  Serial.println("Available WiFi networks:");
  for (int i = 0; i < n; i++) {
    Serial.println(WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)");
  }
}

void connectToNewWiFi() {
  Serial.print("Enter new network SSID: ");
  String ssid = readSerialInput();
  Serial.print("Enter password: ");
  String password = readSerialInput();

  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to: " + ssid + "...");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries++ < wifiRetries) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" ✅ Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
  } else {
    Serial.println(" ❌ Connection failed.");
  }
}

void showConnectionStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to: " + WiFi.SSID());
    Serial.println("IP: " + WiFi.localIP().toString());
    Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
  } else {
    Serial.println("Not connected to WiFi.");
  }
}

void disconnectFromWiFi() {
  WiFi.disconnect();
  Serial.println("Disconnected from WiFi.");
}

String readSerialInput() {
  String input = "";
  while (Serial.available() == 0) {}
  input = Serial.readStringUntil('\n');
  input.trim();
  return input;
}

void serveHTML_P(const char* html_template) {
  String html = FPSTR(html_template);

  String rssi = String(WiFi.RSSI()) + " dBm";
  String rssiPercentage = String(getSignalStrengthPercentage()) + " %";

  html.replace("{{SSID}}", WiFi.SSID());
  html.replace("{{RSSI}}", rssi);
  html.replace("{{RSSI_PERCENT}}", rssiPercentage);
  html.replace("{{TIME}}", timeClient.getFormattedTime());

  if (html.indexOf("{{NETWORK_LIST}}") != -1) {
    int n = WiFi.scanNetworks();
    String list = "<ul>";
    for (int i = 0; i < n; i++) {
      int signalStrength = getSignalStrengthPercentage(i);
      list += "<li>" + WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm, " + String(signalStrength) + " %)</li>";
    }
    list += "</ul>";
    html.replace("{{NETWORK_LIST}}", list);
  }

  server.send(200, "text/html", html);
}
