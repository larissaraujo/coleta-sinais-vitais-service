#ifndef RESOURCE_MODELS_H
#define RESOURCE_MODELS_H

#include <../lib/fhir/DataTypeModels.h>

struct Observation {
    CodeableConcept code;
    const char* effectiveDateTime;
    Quantity valueQuantity;
};

#endif