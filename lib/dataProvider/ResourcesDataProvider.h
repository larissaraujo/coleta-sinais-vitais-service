#ifndef RESOURCES_PROVIDER
#define RESOURCES_PROVIDER

#include <../lib/fhir/ResourceModels.h>
#include <list>

void postBatch(std::list<Observation> observations, std::string communications);

#endif