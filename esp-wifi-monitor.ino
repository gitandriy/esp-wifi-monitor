#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";

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

void setup() {
  Serial.begin(115200);
  delay(1000); // allow serial monitor to start

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) { // can't do below bit without first waiting for connection
    delay(500); // gives time for wifi to connect (wifi.begin)
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.println("In your browser, connect to http://" + WiFi.localIP().toString());
  
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
}