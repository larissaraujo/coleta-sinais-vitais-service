# include <ArduinoJson.h>
#include <../lib/WifiConfig.h>
#include <../lib/MedpumRoutes.h>
#include <../lib/MedplumCertificate.h>
#include <../lib/OAuthDataProvider.h>

std::string token;
std::mutex mutexToken;

void getAccessToken() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    Serial.println("[HTTPS] begin...");
    auto requestUrl = oauth::AUTHENTICATION_URL;
    if (http.begin(requestUrl.toString().c_str(), MEDPLUM_API_CERTIFICATE)) {
      Serial.println("[HTTPS] POST " + String(requestUrl.toString().c_str()));
      http.addHeader(headers::CONTENT_TYPE, parameterValues::FORM_URLENCODED);
      http.addHeader(headers::ACCEPT, "*/*");
      http.addHeader(headers::ACCEPT_ENCODING, "gzip, deflate, br");
      http.addHeader(headers::CONNECTION, "keep-alive");
      int httpCode = http.POST(String(oauth::AUTHENTICATION_BODY.c_str()));
      Serial.printf("[HTTPS] POST... code: %d\n", httpCode);

      // httpCode will be negative on error
      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK) {
          JsonDocument filter;
          filter["access_token"] = true;
          JsonDocument doc;
          DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));
          if (error) {
            Serial.println("deserializeJson() failed: " + String(error.c_str()));
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
      Serial.println("[HTTPS] Não foi possível conectar-se à " + String(requestUrl.toString().c_str()));
    }
  } else {
    connectWifi();
  }
  token = "";
}
