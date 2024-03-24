#include <../lib/utils/BuildObservations.h>
#include <../lib/utils/Constants.h>

Observation getTemperatureObservation(Measurement measurement) {
    return {
        {{TEMPERATURE_CODE, TEMPERATURE_DISPLAY}, TEMPERATURE_DISPLAY},
        measurement.dateTime.c_str(),
        {
            measurement.value,
            TEMPERATURE_UNIT,
            TEMPERATURE_VALUE_CODE
        }
    };
}

Observation getHeartRateObservation(Measurement measurement) {
    return {
        {{HEART_RATE_CODE, HEART_RATE_DISPLAY}, HEART_RATE_DISPLAY},
        measurement.dateTime.c_str(),
        {
            measurement.value,
            HEART_RATE_UNIT,
            HEART_RATE_VALUE_CODE
        }
    };
}

Observation getOximetryObservation(Measurement measurement) {
    return {
        {{OXIMETRY_CODE, OXIMETRY_DISPLAY}, OXIMETRY_DISPLAY},
        measurement.dateTime.c_str(),
        {
            measurement.value,
            OXIMETRY_UNIT,
            OXIMETRY_VALUE_CODE
        }
    };
}

Observation getObservation(Measurement measurement) {
    switch (measurement.type){
        case TEMPERATURE:
            return getTemperatureObservation(measurement);
            break;
        case HEART_RATE:
            return getHeartRateObservation(measurement);
            break;
        case OXIMETRY:
            return getOximetryObservation(measurement);
            break;
        default:
            break;
    }
}