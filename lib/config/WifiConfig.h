#ifndef WIFI_CONFIG
#define WIFI_CONFIG

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define WIFI_SSID "" // rede wifi
#define WIFI_PASSWORD "" // senha da rede wifi
#define WIFI_TIMEOUT_MS 20000

void connectWifi();

#endif
