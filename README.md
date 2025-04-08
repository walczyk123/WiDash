📡 **WiDash – ESP8266 WiFi Dashboard for Sensor Monitoring**

WiDash is a lightweight web-based dashboard running on an ESP8266 that provides real-time monitoring of sensor data over your local WiFi network. The main focus of this project is to offer a dashboard for displaying sensor readings, such as temperature from a **DS18B20** digital temperature sensor.

The data is presented through a simple HTML interface accessible via a web browser on the local network. Additionally, WiDash offers secondary features like WiFi network scanning, connection management, and a serial debug menu for advanced users.

---

✅ **No need for any external upload tools** – all HTML views are embedded directly into the firmware as `.h` files and served from flash memory.

---

### 🔧 Features:
- **Main Feature**: Real-time sensor data display (e.g., DS18B20 temperature sensor)  
- **Secondary Features**:
  - WiFi connection management (connect/disconnect, scan available networks)  
  - Local time synchronization using NTP  
  - Mobile-friendly web UI  
  - Signal strength displayed in dBm and as percentage  
  - Serial menu interface for manual control and debugging

---

## Setup

To set up your WiDash project, follow these steps:

1. **Configure Wi-Fi Settings**

- Inside the project folder, you'll find a file called `credentials.h.sample`.  
- **Step 1**: Copy `credentials.h.sample` and rename it to `credentials.h`.  

**Windows Command Prompt**:
```cmd
copy credentials.h.sample credentials.h
```

**Windows PowerShell:**
```powershell
Copy-Item credentials.h.sample -Destination credentials.h
```

**Linux/Mac Terminal:**
```sh
cp credentials.h.sample credentials.h
```

- **Step 2**: Open credentials.h in a text editor and update the WiFi credentials with the name (SSID) and password of the network you want to connect to. The following lines in credentials.h should be updated:
```cpp
const char* ssid_default = "Your_SSID";// Your WiFi network name
const char* pass_default = "Your_PASSWORD";// Your WiFi network password
```

2. **Assign Static IP (Optional)**

If you want to assign a static IP to the ESP8266 for easier access, follow these steps:

- **Step 1**: Log in to your router’s web interface and locate the MAC address of your ESP8266 device. The MAC address is printed on some boards on the ESP8266 chip or can be found through your router’s DHCP client list after the ESP8266 connects to the network.

- **Step 2**: In your router’s settings, look for the option to assign a static IP or bind the MAC address to an IP address.

- **Example for most routers**: Go to LAN settings or DHCP settings and add a reservation by entering the MAC address of your ESP8266 and the desired static IP address.

Once done, your ESP8266 will always have the same IP address assigned to it, making it easier to access from any device on your local network.

---

## Upload and Run

Once the WiFi credentials and (optional) static IP are set, upload the sketch to your ESP8266 using the Arduino IDE.

1. Open the **Serial Monitor** and set the baud rate to 115200.
2. Upon boot, the ESP8266 will attempt to connect to the WiFi network. Once connected, it will display its IP address in the Serial Monitor, which you can use to access the dashboard in a browser.

> **Note**: If the ESP8266 fails to connect to the WiFi network after several attempts, double-check the SSID and password in `credentials.h`.
