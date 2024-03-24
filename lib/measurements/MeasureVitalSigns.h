#ifndef MEASURE_VITAL_SIGNS_H
#define MEASURE_VITAL_SIGNS_H

#include <mutex>
#include <list>
#include <../lib/measurements/Measurement.h>

extern std::mutex measurementsMutex;
extern std::list<Measurement> measurements;

extern std::string communications;
extern std::mutex communicationsMutex;

void initializeSensors();
void measureVitalSigns();

#endif