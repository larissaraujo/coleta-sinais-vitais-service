# include <ArduinoJson.h>
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
            xSemaphoreTake(xSemaphoreToken, (TickType_t) 10);
            http.addHeader(AUTHORIZATION, "Bearer " + String(token.c_str()));
            xSemaphoreGive(xSemaphoreToken);
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

std::list<ObservationDefinition> getObservationDefinitions() {
    std::list<ObservationDefinition> referenceRanges;
    referenceRanges.clear();
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        Serial.println("[HTTPS] getReferenceRanges...");
        if (http.begin(OBSERVATION_DEFINITION_API_URL, MEDPLUM_API_CERTIFICATE)) {
            http.addHeader(CONTENT_TYPE, FHIR_JSON);
            http.addHeader(ACCEPT, "*/*");
            http.addHeader(ACCEPT_ENCODING, "gzip, deflate, br");
            xSemaphoreTake(xSemaphoreToken, (TickType_t) 10);
            http.addHeader(AUTHORIZATION, "Bearer " + String(token.c_str()));
            xSemaphoreGive(xSemaphoreToken);
            int httpCode = http.GET();
            Serial.printf("[HTTPS] GET %s code: %d\n", OBSERVATION_DEFINITION_API_URL, httpCode);
            // httpCode will be negative on error
            if (httpCode > 0) {
                if (httpCode == HTTP_CODE_OK) {
                    JsonDocument filter;
                    filter["entry"][0]["resource"] = true;
                    JsonDocument doc;
                    DeserializationError error = deserializeJson(doc, http.getStream(), DeserializationOption::Filter(filter));
                    if (error) {
                        Serial.printf("deserializeJson() failed: %s\n", error.c_str());
                    } else {
                        referenceRanges = convertToObservationDefinition(doc["entry"]);
                        return referenceRanges;
                    }
                }
            } else {
                Serial.printf("[HTTPS] POST... error: %s\n", http.errorToString(httpCode).c_str());
            }
            http.end();
        } else {
            Serial.printf("[HTTPS] Não foi possível conectar-se à %s\n", OBSERVATION_DEFINITION_API_URL);
        }
    }
    return referenceRanges;
}