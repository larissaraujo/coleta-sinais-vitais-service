#ifndef REFERENCE_RANGES_MODELS_H
#define REFERENCE_RANGES_MODELS_H

#include <map>
#include <ResourceModels.h>
#include <../lib/utils/Constants.h>

struct ReferenceValues {
  float minValid;
  float maxValid;
  float low;
  float high;
};

extern std::map<std::string, ReferenceValues> defaultReferenceValues;

ReferenceValues getReferenceValues(ObservationDefinition ref, ReferenceValues defaultValues);
boolean isValid(float value, ReferenceValues reference);
boolean isNotNormal(float value, ReferenceValues reference);

#endif