#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ctc-g-cf1186";
const char* password = "89fc2160ded67";

WebServer server(80);

unsigned long lastUpdate = 0;
float dummyValue = 0;

void handleRoot() {
  String html = "<html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='2'>";  // 2秒ごとに自動更新
  html += "</head><body>";
  html += "<h1>ESP32-S3 センサーモニター(ダミー)</h1>";
  html += "<p>現在の値: " + String(dummyValue) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Wi-Fi接続中");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("接続成功！ IPアドレス: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();  // Webサーバーの処理(非ブロッキング)

  // 1秒ごとにダミー値を更新(本来はセンサー読み取りに置き換える)
  unsigned long now = millis();
  if (now - lastUpdate >= 1000) {
    lastUpdate = now;
    dummyValue = random(0, 1000) / 10.0;  // 0.0〜99.9のランダムな値
  }
}