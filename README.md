📡 **WiDash – ESP8266 WiFi Dashboard for Sensor Monitoring**  
WiDash is a lightweight web-based dashboard running on an ESP8266 that provides real-time monitoring of sensor data over your local WiFi network. The main focus of this project is to offer a dashboard for displaying sensor readings, such as temperature from a **DS18B20** digital temperature sensor.

The data is presented through a simple HTML interface accessible via a web browser on the local network. Additionally, WiDash offers secondary features like WiFi network scanning, connection management, and a serial debug menu for advanced users.

> ✅ **No need for any external upload tools** – all HTML views are embedded directly into the firmware as `.h` files and served from flash memory.

---

### 🔧 Features:
- **Main Feature**: Real-time sensor data display (e.g., DS18B20 temperature sensor)  
- **Secondary Features**:
  - WiFi connection management (connect/disconnect, scan available networks)  
  - Local time synchronization using NTP  
  - Mobile-friendly web UI  
  - Signal strength displayed in dBm and as percentage  
  - Serial menu interface for manual control and debugging  
