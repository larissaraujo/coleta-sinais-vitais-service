#ifndef VITAL_SIGNS
#define VITAL_SIGNS

#include <../fhir/DataTypeModels.h>
#include <../fhir/ResourceModels.h>

enum VitalSignsEnum {
    TEMPERATURE,
    HEART_RATE,
    OXIMETRY
};

namespace Temperature {
    const static char* code = "8310-5";
    const static char* display = "Body temperature";
    const static char* valueCode = "Cel";
    const static char* unit = "C";
    const static Coding coding = {code, display};
    const static CodeableConcept codeableConcept = {coding, display};
}

namespace HeartRate {
    const static char* code = "8867-4";
    const static char* display = "Heart Rate";
    const static char* valueCode = "/min";
    const static char* unit = "beats/minute";
    const static Coding coding = {code, display};
    const static CodeableConcept codeableConcept = {coding, display};
}

namespace Oximetry {
    const static char* code = "2708-6";
    const static char* display = "Oxygen saturation";
    const static char* valueCode = "%";
    const static char* unit = "%";
    const static Coding coding = {code, display};
    const static CodeableConcept codeableConcept = {coding, display};
}

#endif