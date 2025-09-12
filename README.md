# ESP8266 Wi-Fi Monitor

A simple Wi-Fi monitoring dashboard for the ESP8266. This project shows the connection status, IP address, and signal strength (RSSI) of the ESP8266 on a clean, web-based dashboard that updates every second.

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
2. Open `main.ino` in Arduino IDE or PlatformIO.
3. Replace the following with your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
