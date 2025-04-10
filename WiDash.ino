#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "routes.h"
#include "credentials.h"

ESP8266WebServer server(80);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600, 60000);

const int wifiRetries = 3;  // Number of WiFi connection attempts
const int RSSI_MIN = -100;  // Minimum signal level in dBm
const int RSSI_MAX = -50;   // Maximum signal level in dBm

// Setup and loop first
void setup() {
  Serial.begin(115200);
  Serial.println("\n=== WiDash Boot ===");

  // Try to connect using defaults from credentials.h
  WiFi.mode(WIFI_STA);
  connectWiFi(ssid_default, pass_default);

  // Init NTP
  timeClient.begin();

  // Setup routes
  setupRoutes(server);

  // Start server
  server.begin();
  Serial.println("HTTP server started.");

  // Show initial serial menu
  showSerialMenu();
}

void loop() {
  server.handleClient();
  timeClient.update();

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    handleSerialCommand(command);

    showSerialMenu();
  }
}

void handleSerialCommand(const String& command) {
  if (command == "1") {
    connectToWiFi();
    return;
  }

  if (command == "2") {
    listAvailableNetworks();
    return;
  }

  if (command == "3") {
    connectToNewWiFi();
    return;
  }

  if (command == "4") {
    showConnectionStatus();
    return;
  }

  if (command == "5") {
    disconnectFromWiFi();
    return;
  }

  if (command == "exit") {
    Serial.println("Exiting and restarting...");
    delay(1000);
    ESP.restart();
    return;
  }

  Serial.println("Unknown command. Try again.");
}

// Function to connect to WiFi (common code for both saved and new networks)
bool connectWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries++ < wifiRetries) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("Failed to connect.");
    return false;
  }
}

// Function to connect to saved WiFi (default credentials)
void connectToWiFi() {
  connectWiFi(ssid_default, pass_default);
}

// Function to connect to a new WiFi network (user input)
void connectToNewWiFi() {
  Serial.print("Enter new network SSID: ");
  String ssid = readSerialInput();
  Serial.print("Enter password: ");
  String password = readSerialInput();

  connectWiFi(ssid.c_str(), password.c_str());
}

// List available WiFi networks
void listAvailableNetworks() {
  int n = WiFi.scanNetworks();
  Serial.println("Available WiFi networks:");
  for (int i = 0; i < n; i++) {
    Serial.println(WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)");
  }
}

// Show the current WiFi connection status
void showConnectionStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to: " + WiFi.SSID());
    Serial.println("IP: " + WiFi.localIP().toString());
    Serial.println("Signal strength: " + String(WiFi.RSSI()) + " dBm");
  } else {
    Serial.println("Not connected to WiFi.");
  }
}

// Disconnect from the current WiFi network
void disconnectFromWiFi() {
  WiFi.disconnect();
  Serial.println("Disconnected from WiFi.");
}

// Show serial menu
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

// Read input from Serial
String readSerialInput() {
  String input = "";
  while (Serial.available() == 0) {}
  input = Serial.readStringUntil('\n');
  input.trim();
  return input;
}

// Serve HTML from memory (embedded)
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

// Function to calculate signal strength percentage
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
