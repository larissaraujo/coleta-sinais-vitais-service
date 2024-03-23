#include <../lib/config/WifiConfig.h>

#define GMT_OFFSET_SEC -3*3600
#define DAY_SAVE_TIME 0*3600

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.printf("Conectando-se à rede '%s'\n", WIFI_SSID);
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado");
  configTime(GMT_OFFSET_SEC, DAY_SAVE_TIME, "time.nist.gov", "0.pool.ntp.org", "1.pool.ntp.org");
}