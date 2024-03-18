#ifndef WIFI_CONFIG
#define WIFI_CONFIG

#include <Arduino.h>

#define WIFI_SSID "Aguinaldo" // rede wifi
#define WIFI_PASSWORD "dinho281" // senha da rede wifi
#define WIFI_TIMEOUT_MS 20000

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
;}

#endif