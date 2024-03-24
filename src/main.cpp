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

void taskSendDataToServer(void *pvParameters) {
  std::list<Observation> observations;
  std::string message = "";
  vTaskDelay(5000);
  while (true) {
    measurementsMutex.lock();
      for(Measurement m : measurements) {
        observations.push_back(getObservation(m));
      }
      measurements.clear();
    measurementsMutex.unlock();
    communicationsMutex.lock();
      message = communications;
      communications = "";
    communicationsMutex.unlock();
    if (!observations.empty() || message != "") {
      postBatch(observations, message);
      observations.clear();
      message = "";
    }
    vTaskDelay(60000);
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);

  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 3000, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 4000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskSendDataToServer, "taskSendDataToServer", 5000, NULL, 3, NULL, 0);

  delay(500);
}

void loop() {}