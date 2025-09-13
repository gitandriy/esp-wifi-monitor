# ESP8266 Wi-Fi Monitor

A simple Wi-Fi monitoring dashboard for the ESP8266. This project shows the connection status, IP address, and signal strength (RSSI) of the ESP8266 on a clean, web-based dashboard that updates every second.

---

## Disclaimer
Some parts of this project were generated with AI assistance:

- **AI-assisted:**  
  - The HTML/JavaScript dashboard (`MAIN_page`)  
  - The JSON endpoint (`handleStatus()`)

- **Written and implemented by me:**  
  - ESP8266 server setup, including defining routes and starting the server  
  - Main loop with `server.handleClient()`  
  - Integration of the dashboard and JSON endpoint  
  - Serial monitor messages for IP and connection status  
  - Adjustments and testing to ensure the project works on my network  

I fully understand how the ESP8266 server works, how the data flows between the ESP and the webpage, and have learnt how to implement similar JSON endpoints myself.


---

## Features

- Real-time Wi-Fi status updates via AJAX (no page reload required)
- **OLED Display Support**: Real-time status display on SSD1306 OLED screen
- Displays:
  - Connection status (Connected / Disconnected)
  - IP address
  - Signal strength (RSSI in dBm)
- Simple, styled HTML dashboard
- JSON endpoint `/status.json` for programmatic access
- Works over any local network

---

## Hardware

- ESP8266 (NodeMCU, Wemos D1 Mini, or similar)
- **SSD1306 OLED Display (128x64, I2C)**
  - VCC → 3.3V
  - GND → GND  
  - SDA → D2 (GPIO4)
  - SCL → D1 (GPIO5)
- USB cable for programming

---

## Setup Instructions

1. **Install Required Libraries**
   - In Arduino IDE, go to **Tools → Manage Libraries**
   - Search and install:
     - `Adafruit SSD1306` by Adafruit
     - `Adafruit GFX Library` by Adafruit
   
2. **Hardware Connection**
   - Connect the SSD1306 OLED display as shown in the Hardware section above
   
3. **Software Setup**
   - Clone or download this repository
   - Open `esp-wifi-monitor.ino` in Arduino IDE or PlatformIO
   - Replace the following with your Wi-Fi credentials:

```cpp
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
```

4. **Upload the Code**
   - Select your ESP8266 board in **Tools → Board**
   - Select the correct port in **Tools → Port**
   - Click **Upload**

5. **Monitor Operation**
   - Open **Serial Monitor** (115200 baud) to see connection status
   - The OLED display will show:
     - "WiFi Monitor" and "Starting..." during boot
     - WiFi connection status, IP address, and signal strength when connected
   - Access the web dashboard at the IP address shown on the OLED or Serial Monitor

## OLED Display Information

The OLED display updates every 5 seconds and shows:
- **Title**: "ESP WiFi Monitor" 
- **Status**: "Connected" or "Disconnected"
- **IP Address**: Current local IP when connected
- **RSSI**: Signal strength in dBm when connected

If the OLED display doesn't work, check:
- Wiring connections (especially SDA/SCL)
- I2C address (default 0x3C)
- Power supply (3.3V)

---
