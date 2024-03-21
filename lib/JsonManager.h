#ifndef JSON_MANAGER_H
#define JSON_MANAGER_H

#include <list>

String convertObservation(Observation observation);
String convertBatch(std::list<Observation> observation);

#endif
