#ifndef BUILD_OBSERVATIONS_H
#define BUILD_OBSERVATIONS_H

#include <../lib/measurements/Measurement.h>
#include <../fhir/ResourceModels.h>

Observation getTemperatureObservation(Measurement measurement);
Observation getHeartRateObservation(Measurement measurement);
Observation getOximetryObservation(Measurement measurement);

#endif