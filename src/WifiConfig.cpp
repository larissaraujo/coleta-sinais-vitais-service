#include <../lib/WifiConfig.h>

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Conectando-se à rede '" + String(WIFI_SSID) + "'");
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    //&& (millis() - startAttemptTime) < WIFI_TIMEOUT_MS
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado...");
}