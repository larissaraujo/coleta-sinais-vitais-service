#ifndef MEASURE_VITAL_SIGNS_H
#define MEASURE_VITAL_SIGNS_H

#include <mutex>
#include <list>
#include <../lib/measurements/Measurement.h>

extern std::mutex temperatureMutex;
extern std::list<Measurement> temperatureMeasurements;
extern std::mutex bpmMutex;
extern std::list<Measurement> bpmMeasurements;
extern std::mutex SpO2Mutex;
extern std::list<Measurement> SpO2Measurements;

void initializeSensors();
void measureVitalSigns();

#endif