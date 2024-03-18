#include <Arduino.h>
#include <Wifi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <../lib/Temperature.h>
#include <../lib/MedpumDataProvider.h>

xQueueHandle measurementsQueue;

void taskMeasureTemperature(void *pvParameters) {
  Measurement measurement;
  while (true) {
    measurement = measureTemperature();
    Serial.println(measurement.value);
    //xQueueSend(measurementsQueue, &measurement, portMAX_DELAY);
    vTaskDelay(TEMPERATURE_MEASUREMENT_PERIOD);
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
  measurementsQueue = xQueueCreate(5, sizeof(float));

  if (measurementsQueue == NULL)  {
     Serial.println("Erro: nao e possivel criar a fila");
     while(1); /* Sem a fila o funcionamento esta comprometido. Nada mais deve ser feito. */
  } 

  xTaskCreatePinnedToCore(taskMeasureTemperature, "taskMeasureTemperature", 1000, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(taskGetAcessToken, "taskGetAcessToken", 5000, NULL, 2, NULL, 0);

  delay(500);
}

void loop() {}