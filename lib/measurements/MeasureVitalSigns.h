#ifndef MEASURE_VITAL_SIGNS_H
#define MEASURE_VITAL_SIGNS_H

#include <list>
#include <../lib/measurements/Measurement.h>

extern std::list<Measurement> measurements;
extern SemaphoreHandle_t xSemaphoreMeasurements;
extern std::string communications;
extern SemaphoreHandle_t xSemaphoreCommunications;

void initializeSensors();
void measureVitalSigns();

#endif