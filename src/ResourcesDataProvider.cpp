#include <../lib/config/WifiConfig.h>
#include <../lib/config/MedplumCertificate.h>
#include <../lib/utils/Constants.h>
#include <../lib/dataProvider/ResourcesDataProvider.h>
#include <../lib/dataProvider/OAuthDataProvider.h>
#include <../lib/utils/JsonManager.h>

void postBatch(String requestBody) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        Serial.println("[HTTPS] postBatch...");
        if (http.begin(BATCH_API_URL, MEDPLUM_API_CERTIFICATE)) {
            http.addHeader(CONTENT_TYPE, FHIR_JSON);
            http.addHeader(ACCEPT, "*/*");
            http.addHeader(ACCEPT_ENCODING, "gzip, deflate, br");
            mutexToken.lock();
            http.addHeader(AUTHORIZATION, "Bearer " + String(token.c_str()));
            mutexToken.unlock();
            Serial.println(requestBody);
            int httpCode = http.POST(requestBody);
            Serial.printf("[HTTPS] POST %s code: %d\n", BATCH_API_URL, httpCode);
            if (httpCode != 200) {
                Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.printf("[HTTPS] Não foi possível conectar-se à %s\n", BATCH_API_URL);
        }
    }
}

void postBatch(std::list<Observation> observations, std::string communications) {
    String requestBody = convertBatch(observations, communications);
    postBatch(requestBody);
}