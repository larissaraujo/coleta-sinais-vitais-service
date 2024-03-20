#include <../lib/Measurement.h>
#include <../fhir/ResourceModels.h>

Observation getTemperatureObservation(Measurement measurement) {
    return {
        Temperature::codeableConcept,
        "2024-03-19",
        {
            measurement.value,
            Temperature::unit,
            Temperature::valueCode
        }
    };
}

Observation getHeartRateObservation(Measurement measurement) {
    return {
        HeartRate::codeableConcept,
        "2024-03-19",
        {
            measurement.value,
            HeartRate::unit,
            HeartRate::valueCode
        }
    };
}

Observation getOximetryObservation(Measurement measurement) {
    return {
        Oximetry::codeableConcept,
        "2024-03-19",
        {
            measurement.value,
            Oximetry::unit,
            Oximetry::valueCode
        }
    };
}

Observation toObservation(Measurement measurement) {
    switch (measurement.vitalSignType) {
        case VitalSignsEnum::TEMPERATURE:
            return getTemperatureObservation(measurement);
            break;
        case VitalSignsEnum::HEART_RATE:
            return getHeartRateObservation(measurement);
            break;
        case VitalSignsEnum::OXIMETRY:
            return getOximetryObservation(measurement);
            break;
        default:
            break;
    }
}

