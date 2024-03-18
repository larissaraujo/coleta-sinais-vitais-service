#ifndef RESOURCE_MODELS_H
#define RESOURCE_MODELS_H

#include <../lib/fhir/DataTypeModels.h>

struct Observation {
    const char* status;
    CodeableConcept code;
    const char* effectiveDateTime;
    Quantity valueQuantity;
};

#endif