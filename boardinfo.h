#ifndef BOARDINFO_H
#define BOARDINFO_H

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

int rssiToPercentage(int rssi) {
  const int RSSI_MIN = -100;
  const int RSSI_MAX = -50;
  if (rssi <= RSSI_MIN) return 0;
  if (rssi >= RSSI_MAX) return 100;
  return map(rssi, RSSI_MIN, RSSI_MAX, 0, 100);
}

String getSSID() {
  return WiFi.SSID();
}

String getRSSI() {
  return String(WiFi.RSSI()) + " dBm";
}

String getRSSIPercent() {
  return String(rssiToPercentage(WiFi.RSSI())) + " %";
}

String getIP() {
  return WiFi.localIP().toString();
}

String getMAC() {
  return WiFi.macAddress();
}

String getTime(NTPClient& timeClient) {
  return timeClient.getFormattedTime();
}

String getUptime() {
  return String(millis() / 1000) + " s";
}

String getFreeRAM() {
  return String(ESP.getFreeHeap()) + " B";
}

String getMaxRAM() {
  return "Max RAM info unavailable";
}

String getFlashSize() {
  return String(ESP.getFlashChipSize()) + " B";
}

String getMaxFlashSize() {
  return String(ESP.getFlashChipSize()) + " B";
}

String getSDKVersion() {
  return String(ESP.getSdkVersion());
}

String getCPUFrequency() {
  return String(ESP.getCpuFreqMHz()) + " MHz";
}

#endif
