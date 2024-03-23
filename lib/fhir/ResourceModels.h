#ifndef RESOURCE_MODELS_H
#define RESOURCE_MODELS_H

#include <list>
#include <Arduino.h>
#include <../lib/fhir/DataTypeModels.h>

struct Observation {
    CodeableConcept code;
    String effectiveDateTime;
    Quantity valueQuantity;
};

#endif