#include <../lib/utils/ReferenceRanges.h> 

std::map<std::string, ReferenceValues> defaultReferenceValues = {
    {TEMPERATURE_CODE, {30.0, 45.0, 35.0, 37.8}},
    {HEART_RATE_CODE, {0.0, 250.0, 50.0, 100.0}},
    {OXIMETRY_CODE, {0.0, 100.0, 95.0, 100.0}},
};

boolean isValid(float value, ReferenceValues reference) {
  return value > reference.minValid && value < reference.maxValid;
}

boolean isNotNormal(float value, ReferenceValues reference) {
    return value < reference.low || value > reference.high;
}

std::pair<bool, Range> findByRangeCategory(std::list<ObservationDefinitionQualifiedInterval> intervals, String category) {
    for (auto interval : intervals) {
        if (interval.category == category) {
            std::pair<bool, Range> range(true, interval.range);
            return range;
        }
    }
    std::pair<bool, Range> range(false, {});
    return range;
}

ReferenceValues getReferenceValues(ObservationDefinition ref, ReferenceValues defaultValues) {
  float minValid, maxValid, high, low;
  auto absolute = findByRangeCategory(ref.qualifiedInterval, "absolute");
    if (absolute.first) {
        minValid = absolute.second.low.value;
        maxValid = absolute.second.high.value;
    } else {
        minValid = defaultValues.minValid;
        maxValid = defaultValues.maxValid;
    }
    auto reference = findByRangeCategory(ref.qualifiedInterval, "reference");
    if (reference.first) {
        low = reference.second.low.value;
        high = reference.second.high.value;
    } else {
        low = defaultValues.low;
        high = defaultValues.high;
    }
    return { minValid, maxValid, low, high };
}