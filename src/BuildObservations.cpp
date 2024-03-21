#include <../lib/BuildObservations.h>

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

