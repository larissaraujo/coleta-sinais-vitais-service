#ifndef RESOURCES_PROVIDER
#define RESOURCES_PROVIDER

#include <../lib/fhir/ResourceModels.h>
#include <list>

std::list<ObservationDefinition> getObservationDefinitions();
void postBatch(std::list<Observation> observations, std::string communications);

#endif