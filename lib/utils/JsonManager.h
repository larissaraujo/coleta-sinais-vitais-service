#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <Arduino.h>
#include <list>
#include <../lib/fhir/ResourceModels.h>

String convertObservation(Observation observation);
String convertBatch(std::list<Observation> observation);

#endif
