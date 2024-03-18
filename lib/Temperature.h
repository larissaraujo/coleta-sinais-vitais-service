#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <../lib/fhir/ResourceModels.h>
#include <../lib/Measurement.h>

#define TEMPERATURE_MEASUREMENT_PERIOD 5000

Measurement measureTemperature();

#endif