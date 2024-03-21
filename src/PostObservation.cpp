#include <../lib/WifiConfig.h>
#include <../lib/MedpumRoutes.h>
#include <../lib/MedplumCertificate.h>
#include <../lib/ObservationDataProvider.h>
#include <../lib/OAuthDataProvider.h>
#include <../lib/JsonManager.h>

void postObservation(Observation observation) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        auto requestUrl = OBSERVATION_URL;
        if (http.begin(requestUrl.toString().c_str(), MEDPLUM_API_CERTIFICATE)) {
            Serial.println("[HTTPS] POST " + String(requestUrl.toString().c_str()));
            http.addHeader(headers::CONTENT_TYPE, parameterValues::FHIR_JSON);
            http.addHeader(headers::ACCEPT, "*/*");
            http.addHeader(headers::ACCEPT_ENCODING, "gzip, deflate, br");
            mutexToken.lock();
            http.addHeader(headers::AUTHORIZATION, "Bearer " + String(token.c_str()));
            mutexToken.unlock();
            String requestBody = convertObservation(observation);
            Serial.println(requestBody);
            int httpCode = http.POST(requestBody);
            Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
            if (httpCode != 201) {
                Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.println("[HTTPS] Não foi possível conectar-se à " + String(requestUrl.toString().c_str()));
        }
    }
}

void postObservations(std::list<Observation> observations) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        auto requestUrl = BATCH_URL;
        if (http.begin(requestUrl.toString().c_str(), MEDPLUM_API_CERTIFICATE)) {
            Serial.println("[HTTPS] POST " + String(requestUrl.toString().c_str()));
            http.addHeader(headers::CONTENT_TYPE, parameterValues::FHIR_JSON);
            http.addHeader(headers::ACCEPT, "*/*");
            http.addHeader(headers::ACCEPT_ENCODING, "gzip, deflate, br");
            mutexToken.lock();
            http.addHeader(headers::AUTHORIZATION, "Bearer " + String(token.c_str()));
            mutexToken.unlock();
            String requestBody = convertBatch(observations);
            Serial.println(requestBody);
            int httpCode = http.POST(requestBody);
            Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
            if (httpCode != 200) {
                Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.println("[HTTPS] Não foi possível conectar-se à " + String(requestUrl.toString().c_str()));
        }
    }
}