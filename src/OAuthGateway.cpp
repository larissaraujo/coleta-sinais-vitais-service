# include <ArduinoJson.h>
#include <../lib/config/WifiConfig.h>
#include <../lib/config/MedplumCertificate.h>
#include <../lib/utils/Constants.h>
#include <../lib/dataProvider/OAuthDataProvider.h>

std::string token;
std::mutex mutexToken;

void getAccessToken() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println("[HTTPS] getAccessToken...");
    if (http.begin(AUTHENTICATION_API_URL, MEDPLUM_API_CERTIFICATE)) {
      http.addHeader(CONTENT_TYPE, FORM_URLENCODED);
      http.addHeader(ACCEPT, "*/*");
      http.addHeader(ACCEPT_ENCODING, "gzip, deflate, br");
      http.addHeader(CONNECTION, "keep-alive");
      
      int httpCode = http.POST(AUTHENTICATION_REQUEST_BODY);
      Serial.printf("[HTTPS] POST %s code: %d\n", AUTHENTICATION_API_URL, httpCode);

      // httpCode will be negative on error
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          JsonDocument filter;
          filter["access_token"] = true;
          JsonDocument doc;
          DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));
          if (error) {
            Serial.printf("deserializeJson() failed: %s\n", error.c_str());
            return;
          }
          const char* accessToken = doc["access_token"]; 
          mutexToken.lock();
          token.assign(accessToken);
          mutexToken.unlock();
          return;
        }
      } else {
        Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
    } else {
      Serial.printf("[HTTPS] Não foi possível conectar-se à %s\n", AUTHENTICATION_API_URL);
    }
  } else {
    connectWifi();
  }
  token = "";
}
