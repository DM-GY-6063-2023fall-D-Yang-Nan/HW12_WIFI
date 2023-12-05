#include <WebServer.h>
#include <WiFi.h>
#include "esp_wpa2.h"

#include <ArduinoJson.h>

#include "config.h" // 确保您有一个config.h文件包含SSID和SSID_PASSWORD
const char* SSID = "Verizon_R3S4K9";
const char* SSID_PASSWORD = "churn6-boa-hale";
// WiFi 代码
WebServer server(80);

// 项目变量
int a0Val = 0;
int d2Val = 0;
int d3Val = 0; // D3按钮状态
int d4Val = 0; // D4按钮状态
int d2ClickCount = 0;

int prevD2Val = 0;

// WiFi 函数
void handleNotFound() {
  server.send(404, "text/plain", "404! 地址未找到");
}

void handleData() {
  StaticJsonDocument<256> resJson;
  JsonObject data = resJson.createNestedObject("data");
  JsonObject A0 = data.createNestedObject("A0");
  JsonObject D2 = data.createNestedObject("D2");
  JsonObject D3 = data.createNestedObject("D3");
  JsonObject D4 = data.createNestedObject("D4");

  A0["value"] = a0Val;
  D2["isPressed"] = d2Val;
  D2["count"] = d2ClickCount;
  D3["isPressed"] = d3Val;
  D4["isPressed"] = d4Val;

  String resTxt = "";
  serializeJson(resJson, resTxt);

  server.send(200, "application/json", resTxt);
}

void setup() {
  // WiFi 设置
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
    Serial.println("IP 地址: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi未连接!");
  }

  server.enableCORS();
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();

  // 项目设置
  pinMode(2, INPUT);
 pinMode(3, INPUT_PULLUP); // 初始化D3
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  // 读取引脚
  a0Val = analogRead(A0);
  d2Val = digitalRead(2);
 d3Val = digitalRead(3) == LOW;
  d4Val = digitalRead(4) == LOW;

  // 计算D2是否被点击
  if (d2Val && d2Val != prevD2Val) {
    d2ClickCount++;
  }

  prevD2Val = d2Val;

  // WiFi 代码
  server.handleClient();
  delay(2);

}
