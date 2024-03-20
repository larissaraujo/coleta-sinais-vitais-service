#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include <../lib/Measurement.h>

void createMeasurementsQueue();
void addMeasurementToQueue(Measurement measurement);
Measurement removeMeasurementToQueue();

#endif