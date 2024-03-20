#include <../lib/QueueManager.h>

xQueueHandle measurementsQueue;
xQueueHandle alertsQueue;

void createMeasurementsQueue() {
    measurementsQueue = xQueueCreate(5, sizeof(Measurement));

  if (measurementsQueue == NULL)  {
     Serial.println("Erro: nao e possivel criar a fila");
     while(1); /* Sem a fila o funcionamento esta comprometido. Nada mais deve ser feito. */
  } 
}

void addMeasurementToQueue(Measurement measurement) {
    xQueueSend(measurementsQueue, &measurement, portMAX_DELAY);
}

Measurement removeMeasurementToQueue() {
    Measurement measurement;
    xQueueReceive(measurementsQueue, &measurement, portMAX_DELAY);
    Serial.println(String(measurement.vitalSignType));
    return measurement;
}