#ifndef RESOURCE_MODELS_H
#define RESOURCE_MODELS_H

#include <list>
#include <../lib/fhir/DataTypeModels.h>

struct Observation {
    CodeableConcept code;
    const char* effectiveDateTime;
    Quantity valueQuantity;
};

struct Request {
    char* method;
    char* url;
};

struct Entry {
    Observation resource;
    Request request;
};

struct Batch {
    char* resourceType;
    char* type;
    std::list<Entry> entry;
};

#endif