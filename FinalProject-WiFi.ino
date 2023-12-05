#include <WebServer.h>
#include <WiFi.h>
#include "esp_wpa2.h"

#include <ArduinoJson.h>

#include "config.h"

// WiFi code
WebServer server(80);

// project variables
int a0Val = 0;
int d2Val = 0;
int d2ClickCount = 0;

int prevD2Val = 0;

// WiFi function
void handleNotFound() {
  server.send(404, "text/plain", "404! ADDRESS NOT FOUND");
}

void handleData() {
  StaticJsonDocument<128> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");
  JsonObject D2 = data.createNestedObject("D2");

  A0["value"] = a0Val;
  D2["isPressed"] = d2Val;
  D2["count"] = d2ClickCount;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  server.send(200, "application/json", resTxt);
}

void setup() {
  // WiFi setup
  Serial.begin(9600);
  while (!Serial) {}

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, SSID_PASSWORD);

  int tryConnectCount = 0;
  while (WiFi.status() != WL_CONNECTED && tryConnectCount < 60) {
    delay(500);
    Serial.print(".");
    tryConnectCount++;
  }
  Serial.println("");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi is NOT connected! 💩");
  }

  server.enableCORS();
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();

  // project setup
  pinMode(2, INPUT);
}

void loop() {
  // read pins
  a0Val = analogRead(A0);
  d2Val = digitalRead(2);

  // calculate if d2 was clicked
  if (d2Val && d2Val != prevD2Val) {
    d2ClickCount++;
  }

  prevD2Val = d2Val;

  // WiFi code
  server.handleClient();
  delay(2);
}
