#include <HTTPClient.h>
#include <Wire.h>
#include <list>
#include <../lib/utils/Constants.h>
#include <../lib/measurements/MeasureVitalSigns.h>
#include <../lib/utils/BuildObservations.h>
#include <../lib/dataProvider/OAuthDataProvider.h>
#include <../lib/dataProvider/ResourcesDataProvider.h>

void taskMeasureVitalSigns(void *pvParameters) {
  initializeSensors();
  while (true) {
    measureVitalSigns();
  }
}

void taskGetAcessToken(void *pvParameters) {
  while (true) {
    getAccessToken();
    mutexToken.lock();
    if (token != "") {
      mutexToken.unlock();
      vTaskDelay(3600000);
    } else {
      mutexToken.unlock();
      vTaskDelay(500);
    }
  }
}

void taskPostObservation(void *pvParameters) {
  std::list<Observation> observations;
  vTaskDelay(5000);
  while (true) {
    temperatureMutex.lock();
    for(Measurement m : temperatureMeasurements) {
      observations.push_back(getTemperatureObservation(m));
    }
    temperatureMeasurements.clear();
    temperatureMutex.unlock();
    bpmMutex.lock();
    for(Measurement m : bpmMeasurements) {
      observations.push_back(getHeartRateObservation(m));
    }
    bpmMeasurements.clear();
    bpmMutex.unlock();
    SpO2Mutex.lock();
    for(Measurement m : SpO2Measurements) {
      observations.push_back(getOximetryObservation(m));
    }
    SpO2Measurements.clear();
    SpO2Mutex.unlock();
    std::string message = "";
    communicationsMutex.lock();
    message = communications;
    communications = "";
    communicationsMutex.unlock();
    if (!observations.empty() || message != "") {
      postBatch(observations, message);
      observations.clear();
    }
    vTaskDelay(60000);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 3000, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 4000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskPostObservation, "taskPostObservation", 5000, NULL, 3, NULL, 0);

  delay(500);
}

void loop() {}