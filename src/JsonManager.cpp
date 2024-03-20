#include <ArduinoJson.h>
#include "../lib/Constants.h"
#include "../lib/fhir/ResourceModels.h"
#include <../lib/JsonManager.h>

String convertObservation(Observation observation) {
    JsonDocument doc;

    doc["resourceType"] = FHIR::RESOURCE_OBSERVATION;
    //doc["meta"]["profile"][0] = "http://hl7.org/fhir/us/core/StructureDefinition/us-core-head-circumference";
    doc["status"] = FHIR::STATUS_PRELIMINARY;

    JsonObject subject = doc["subject"].to<JsonObject>();
    subject["reference"]  = FHIR::PATIENT_ID;

    JsonObject category = doc["category"][0]["coding"].add<JsonObject>();
    category["system"] = FHIR::OBSERVATION_CATEGORY_SYSTEM;
    category["code"] = FHIR::OBSERVATION_CATEGORY_CODE;
    category["display"] = FHIR::OBSERVATION_CATEGORY_DYSPLAY;

    JsonObject code = doc["code"].to<JsonObject>();
    JsonObject coding = code["coding"].add<JsonObject>();
    coding["system"] = FHIR::OBSERVATION_CODE_SYSTEM;
    coding["code"] = observation.code.coding->code;
    coding["display"] = observation.code.coding->display;
    code["text"] = observation.code.text;

    doc["effectiveDateTime"] = observation.effectiveDateTime;

    JsonObject valueQuantity = doc["valueQuantity"].to<JsonObject>();
    valueQuantity["value"] = observation.valueQuantity.value;
    valueQuantity["unit"] = observation.valueQuantity.unit;
    valueQuantity["system"] = FHIR::OBSERVATION_QUANTITY_SYSTEM;
    valueQuantity["code"] = observation.valueQuantity.code;

    String output;
    doc.shrinkToFit();  // optional
    serializeJson(doc, output);
    return output;
}

