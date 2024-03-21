#include <HTTPClient.h>
#include <Wire.h>
#include <list>
#include <../lib/MeasureVitalSigns.h>
#include <../lib/BuildObservations.h>
#include <../lib/OAuthDataProvider.h>
#include <../lib/ObservationDataProvider.h>

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
    Serial.println(temperatureMeasurements.size());
    for(Measurement m : temperatureMeasurements) {
      observations.push_back(getTemperatureObservation(m));
      Serial.println(m.value);
    }
    temperatureMeasurements.clear();
    temperatureMutex.unlock();
    bpmMutex.lock();
    Serial.println(bpmMeasurements.size());
    for(Measurement m : bpmMeasurements) {
      observations.push_back(getHeartRateObservation(m));
      Serial.println(m.value);
    }
    bpmMeasurements.clear();
    bpmMutex.unlock();
    SpO2Mutex.lock();
    Serial.println(SpO2Measurements.size());
    for(Measurement m : SpO2Measurements) {
      observations.push_back(getOximetryObservation(m));
      Serial.println(m.value);
    }
    SpO2Measurements.clear();
    SpO2Mutex.unlock();
    if (!observations.empty()) {
      postObservations(observations);
      observations.clear();
    }
    vTaskDelay(60000);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 5000, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 5000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskPostObservation, "taskPostObservation", 5000, NULL, 2, NULL, 0);

  delay(500);
}

void loop() {}