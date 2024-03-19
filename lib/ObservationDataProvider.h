#ifndef OBSERVATION_PROVIDER
#define OBSERVATION_PROVIDER

#include <mutex>
#include <../lib/fhir/ResourceModels.h>

void postObservation(Observation observation);

#endif