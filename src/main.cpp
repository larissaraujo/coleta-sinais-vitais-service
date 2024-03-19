#include <Arduino.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <../lib/MeasureVitalSigns.h>
#include <../lib/MedpumDataProvider.h>

xQueueHandle measurementsQueue;

void taskMeasureVitalSigns(void *pvParameters) {
  initializateSensors();
  while (true) {
    measureVitalSigns();
    //xQueueSend(measurementsQueue, &measurement, portMAX_DELAY);
    //vTaskDelay(1000);
  }
}

void taskGetAcessToken(void *pvParameters) {
  while (true) {
    Serial.println(token);
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

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  measurementsQueue = xQueueCreate(5, sizeof(float));

  if (measurementsQueue == NULL)  {
     Serial.println("Erro: nao e possivel criar a fila");
     while(1); /* Sem a fila o funcionamento esta comprometido. Nada mais deve ser feito. */
  } 

  xTaskCreatePinnedToCore(taskMeasureVitalSigns, "taskMeasureVitalSigns", 5000, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 5000, NULL, 2, NULL, 0);

  delay(500);
}

void loop() {}