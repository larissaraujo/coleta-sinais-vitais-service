#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <Arduino.h>

enum VitalSign {
    TEMPERATURE,
    HEART_RATE,
    OXIMETRY
};

struct Measurement {
    float value;
    String dateTime;
    VitalSign type;
};

#endif