#ifndef DATA_TYPE_MODELS_H
#define DATA_TYPE_MODELS_H

struct Coding {
    const char* code;
    const char* display;
};

struct CodeableConcept {
    Coding coding[1];
    const char* text;
};

struct Quantity {
    const float value;
    const char* unit;
    const char* code;
};

struct Range {
    Quantity low;
    Quantity high;
};

struct ObservationDefinitionQualifiedInterval {
    String category;
    Range range;
    CodeableConcept context;
    CodeableConcept appliesTo;
    String gender;
    Range age;
    Range gestationalAge;
    String condition;
};

#endif