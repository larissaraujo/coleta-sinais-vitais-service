#ifndef MEASURE_VITAL_SIGNS_H
#define MEASURE_VITAL_SIGNS_H

#include <list>
#include <map>
#include <../lib/measurements/Measurement.h>
#include <../lib/fhir/ResourceModels.h>
#include <../lib/utils/ReferenceRanges.h>

extern std::list<Measurement> measurements;
extern SemaphoreHandle_t xSemaphoreMeasurements;
extern std::string communications;
extern SemaphoreHandle_t xSemaphoreCommunications;
extern std::map<std::string, ReferenceValues> referenceRanges;
extern SemaphoreHandle_t xSemaphoreReferenceRanges;

void initializeSensors();
void measureVitalSigns();

#endif