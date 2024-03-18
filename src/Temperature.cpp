#include "../lib/Temperature.h"
#include <../lib/Constants.h>
#include <../lib/VitalSigns.h>

OneWire oneWire(4);
DallasTemperature sensor(&oneWire);

Measurement measureTemperature() {
    sensor.requestTemperatures();
    return {
        sensor.getTempCByIndex(0),
        millis(),
        "TEMPERATURE"
    };
}

// Observation getObservation(float value) {
//     return {
//         "preliminary",
//         {
//             {
//                 TEMPERATURE::code,
//                 TEMPERATURE::display
//             },
//             TEMPERATURE::display
//         },
//         "2024-03-16T21:39:00Z",
//         {
//             value,
//             TEMPERATURE::unit,
//             TEMPERATURE::valueCode
//         }
//     };
// }