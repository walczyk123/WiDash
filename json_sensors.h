#ifndef SENSORS_JSON_H
#define SENSORS_JSON_H

#include <Arduino.h>
#include <NTPClient.h>

// Typ struktury pojedynczego czujnika
struct SensorReading {
  String address;
  String name;
  float value;
};

// Przykładowa mapa adresów do nazw
const SensorReading dummySensors[] = {
  {"28FF641D6216031A", "inside temperature", 22.5},
  {"28FF3C1A5C16039B", "outside temperature", 15.2}
};
const int dummySensorCount = sizeof(dummySensors) / sizeof(dummySensors[0]);

// Funkcja generująca JSON
String generateSensorsJson(NTPClient& timeClient) {
  String json = "[\n";
  for (int i = 0; i < dummySensorCount; ++i) {
    json += "  {\n";
    json += "    \"sensor_address\": \"" + dummySensors[i].address + "\",\n";
    json += "    \"sensor_name\": \"" + dummySensors[i].name + "\",\n";
    json += "    \"reading\": " + String(dummySensors[i].value, 2) + ",\n";
    json += "    \"time\": \"" + timeClient.getFormattedTime() + "\"\n";
    json += "  }";
    if (i < dummySensorCount - 1) json += ",";
    json += "\n";
  }
  json += "]";
  return json;
}

#endif
