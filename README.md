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
- USB cable for programming
- Optional: Access to a Wi-Fi network

---

## Setup Instructions

1. Clone or download this repository.
2. Open `esp-wifi-monitor.ino` in Arduino IDE or PlatformIO.
3. Replace the following with your Wi-Fi credentials:

```cpp
const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
