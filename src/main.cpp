#include <HTTPClient.h>
#include <Wire.h>
#include <../lib/MeasureVitalSigns.h>
#include <../lib/OAuthDataProvider.h>
#include <../lib/ObservationDataProvider.h>
#include <../lib/QueueManager.h>

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
  while (true) {
    Measurement measurement = removeMeasurementToQueue();
    postObservation(toObservation(measurement));
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  createMeasurementsQueue();

  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 5000, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 5000, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(taskPostObservation, "taskPostObservation", 5000, NULL, 2, NULL, 0);

  delay(500);
}

void loop() {}