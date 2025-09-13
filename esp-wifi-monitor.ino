#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ESP8266WebServer server(80); // creates web server on port 80

// string containing html info and css
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>ESP8266 WiFi Monitor</title>
<style>
  body { font-family: Arial; text-align:center; background:#1e1e1e; color:#f0f0f0; }
  .container { background:#2c2c2c; padding:30px 50px; border-radius:10px; display:inline-block; }
  h1 { color:#4caf50; margin-bottom:20px; }
  p { font-size:18px; margin:10px 0; }
  #status.connected { color:#4caf50; }
  #status.disconnected { color:#f44336; }
</style>
</head>
<body>
<div class="container">
  <h1>ESP8266 WiFi Monitor</h1>
  <p>Status: <span id="status">...</span></p>
  <p>IP: <span id="ip">...</span></p>
  <p>RSSI: <span id="rssi">...</span></p>
</div>

<script>
function updateStatus(status, ip, rssi) {
  const statusElem = document.getElementById("status");
  statusElem.innerText = status;
  statusElem.className = status;

  document.getElementById("ip").innerText = ip || "-";
  document.getElementById("rssi").innerText = rssi || "-";
}

// get wifi info from esp every second
async function fetchStatus() {
  try {
    const res = await fetch('/status.json');
    const data = await res.json();
    updateStatus(data.status, data.ip, data.rssi);
  } catch (err) {
    updateStatus("disconnected", "-", "-");
  }
}

setInterval(fetchStatus, 1000);
fetchStatus();
</script>

</body>
</html>
)rawliteral";

// root page
void handleRoot() {
  server.send_P(200, "text/html", MAIN_page);
}

// Function to initialize OLED display
void initializeOLED() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    return;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("WiFi Monitor"));
  display.println(F("Starting..."));
  display.display();
}

// Function to update OLED with WiFi status
void updateOLEDDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  
  display.println(F("ESP WiFi Monitor"));
  display.println(F("----------------"));
  
  if (WiFi.status() == WL_CONNECTED) {
    display.println(F("Status: Connected"));
    display.print(F("IP: "));
    display.println(WiFi.localIP());
    display.print(F("RSSI: "));
    display.print(WiFi.RSSI());
    display.println(F(" dBm"));
  } else {
    display.println(F("Status: Disconnected"));
    display.println(F("Reconnecting..."));
  }
  
  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(1000); // allow serial monitor to start

  // Initialize OLED display
  initializeOLED();

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) { // can't do below bit without first waiting for connection
    delay(500); // gives time for wifi to connect (wifi.begin)
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.println("In your browser, connect to http://" + WiFi.localIP().toString());
  
  // Update OLED with connection status
  updateOLEDDisplay();
  
  // handles default route (root)
  server.on("/", handleRoot);

  // handles status json used in homepage
  server.on("/status.json", handleStatus);


  // start server
  server.begin();
  Serial.println("HTTP server started");

}

void handleStatus() { // creates json containing wifi info
  String json = "{";
  if (WiFi.status() == WL_CONNECTED) {
    json += "\"status\":\"connected\",";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
    json += "\"rssi\":\"" + String(WiFi.RSSI()) + "\"";
  } else {
    json += "\"status\":\"disconnected\"";
  }
  json += "}";
  server.send(200, "application/json", json);
}

void loop() {
  server.handleClient(); // constantly checks for requests to esp8266
  
  // Update OLED display every 5 seconds
  static unsigned long lastOLEDUpdate = 0;
  if (millis() - lastOLEDUpdate > 5000) {
    updateOLEDDisplay();
    lastOLEDUpdate = millis();
  }
}