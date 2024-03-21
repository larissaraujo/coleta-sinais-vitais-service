#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <../lib/VitalSigns.h>

struct Measurement {
    float value;
    unsigned long time;
};

#endif