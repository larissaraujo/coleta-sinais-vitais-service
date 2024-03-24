#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <Arduino.h>
#include <list>
#include <../lib/fhir/ResourceModels.h>

String convertBatch(std::list<Observation> observations, std::string communications);

#endif
