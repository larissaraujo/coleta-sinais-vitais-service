#include <HTTPClient.h>
#include <Wire.h>
#include <list>
#include <../lib/utils/Constants.h>
#include <../lib/measurements/MeasureVitalSigns.h>
#include <../lib/utils/BuildObservations.h>
#include <../lib/dataProvider/OAuthDataProvider.h>
#include <../lib/dataProvider/ResourcesDataProvider.h>

bool sendData = false;

SemaphoreHandle_t xSemaphoreCommunications;
SemaphoreHandle_t xSemaphoreMeasurements;
SemaphoreHandle_t xSemaphoreToken;
SemaphoreHandle_t xSemaphoreReferenceRanges;

void taskMeasureVitalSigns(void *pvParameters) {
  initializeSensors();
  while (true) {
    measureVitalSigns();
  }
}

void initializeReferenceValues() {
  std::list<ObservationDefinition> definitions = getObservationDefinitions();
  xSemaphoreTake(xSemaphoreReferenceRanges, (TickType_t) 10);
  for (ObservationDefinition ref : definitions) {
    referenceRanges[ref.code.c_str()] = getReferenceValues(ref, defaultReferenceValues[ref.code.c_str()]);
  }
  xSemaphoreGive(xSemaphoreReferenceRanges);
}

void taskGetAcessToken(void *pvParameters) {
  while (true) {
    getAccessToken();
    xSemaphoreTake(xSemaphoreToken, (TickType_t) 10);
    if (token != "") {
      xSemaphoreGive(xSemaphoreToken);
      initializeReferenceValues();
      vTaskDelay(portTICK_PERIOD_MS*3600000);
    } else {
      xSemaphoreGive(xSemaphoreToken);
      vTaskDelay(500);
    }
  }
}

void taskSendDataToServer(void *pvParameters) {
  std::list<Observation> observations;
  std::string message = "";
  vTaskDelay(5000);
  while (true) {
    if (sendData) {
      xSemaphoreTake(xSemaphoreMeasurements, (TickType_t) 10);
        for(Measurement m : measurements) {
          observations.push_back(getObservation(m));
        }
        measurements.clear();
      xSemaphoreGive(xSemaphoreMeasurements);
      xSemaphoreTake(xSemaphoreCommunications, (TickType_t) 10);
        message = communications;
        communications = "";
      xSemaphoreGive(xSemaphoreCommunications);
      if (!observations.empty() || message != "") {
        postBatch(observations, message);
        observations.clear();
        message = "";
      }
    }
    vTaskDelay(60000);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  xSemaphoreCommunications = xSemaphoreCreateMutex();
  if(xSemaphoreCommunications == NULL) {
    Serial.printf("Falha ao criar o Mutex para Comunicações\n");
  }

  xSemaphoreMeasurements = xSemaphoreCreateMutex();
  if(xSemaphoreMeasurements == NULL) {
    Serial.printf("Falha ao criar o Mutex para Medições\n");
  }

  xSemaphoreToken = xSemaphoreCreateMutex();
  if(xSemaphoreToken == NULL) {
    Serial.printf("Falha ao criar o Mutex para Token de acesso\n");
  }

  xSemaphoreReferenceRanges = xSemaphoreCreateMutex();
  if(xSemaphoreReferenceRanges == NULL) {
    Serial.printf("Falha ao criar o Mutex para Intervalos de Referência\n");
  }
  
  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 3000, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 4000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskSendDataToServer, "taskSendDataToServer", 5000, NULL, 3, NULL, 0);

  delay(500);
}

void loop() {}