#ifndef OBSERVATION_PROVIDER
#define OBSERVATION_PROVIDER

#include <../lib/fhir/ResourceModels.h>
#include <list>

void postObservation(Observation observation);
void postObservations(std::list<Observation> observations);

#endif