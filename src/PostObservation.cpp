#include <../lib/config/WifiConfig.h>
#include <../lib/config/MedplumCertificate.h>
#include <../lib/utils/Constants.h>
#include <../lib/dataProvider/ObservationDataProvider.h>
#include <../lib/dataProvider/OAuthDataProvider.h>
#include <../lib/utils/JsonManager.h>

void postObservation(Observation observation) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        Serial.println("[HTTPS] postObservation...");
        if (http.begin(OBSERVATION_API_URL, MEDPLUM_API_CERTIFICATE)) {
            http.addHeader(CONTENT_TYPE, FHIR_JSON);
            http.addHeader(ACCEPT, "*/*");
            http.addHeader(ACCEPT_ENCODING, "gzip, deflate, br");
            mutexToken.lock();
            http.addHeader(AUTHORIZATION, "Bearer " + String(token.c_str()));
            mutexToken.unlock();
            String requestBody = convertObservation(observation);
            Serial.println(requestBody);
            int httpCode = http.POST(requestBody);
            Serial.printf("[HTTPS] POST %s code: %d\n", OBSERVATION_API_URL, httpCode);
            if (httpCode != 201) {
                Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.printf("[HTTPS] Não foi possível conectar-se à %s\n", OBSERVATION_API_URL);
        }
    }
}

void postObservations(std::list<Observation> observations) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        Serial.println("[HTTPS] postObservations...");
        if (http.begin(BATCH_API_URL, MEDPLUM_API_CERTIFICATE)) {
            http.addHeader(CONTENT_TYPE, FHIR_JSON);
            http.addHeader(ACCEPT, "*/*");
            http.addHeader(ACCEPT_ENCODING, "gzip, deflate, br");
            mutexToken.lock();
            http.addHeader(AUTHORIZATION, "Bearer " + String(token.c_str()));
            mutexToken.unlock();
            String requestBody = convertBatch(observations);
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