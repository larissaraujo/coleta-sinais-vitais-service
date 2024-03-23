#include <ArduinoJson.h>
#include "../lib/utils/Constants.h"
#include "../lib/fhir/ResourceModels.h"
#include <../lib/utils/JsonManager.h>

String convertObservation(Observation observation) {
    JsonDocument doc;

    doc["resourceType"] = RESOURCE_OBSERVATION;
    //doc["meta"]["profile"][0] = "http://hl7.org/fhir/us/core/StructureDefinition/us-core-head-circumference";
    doc["status"] = STATUS_PRELIMINARY;

    JsonObject subject = doc["subject"].to<JsonObject>();
    subject["reference"]  = PATIENT_ID;

    JsonObject category = doc["category"][0]["coding"].add<JsonObject>();
    category["system"] = OBSERVATION_CATEGORY_SYSTEM;
    category["code"] = OBSERVATION_CATEGORY_CODE;
    category["display"] = OBSERVATION_CATEGORY_DYSPLAY;

    JsonObject code = doc["code"].to<JsonObject>();
    JsonObject coding = code["coding"].add<JsonObject>();
    coding["system"] = OBSERVATION_CODE_SYSTEM;
    coding["code"] = observation.code.coding->code;
    coding["display"] = observation.code.coding->display;
    code["text"] = observation.code.text;

    doc["effectiveDateTime"] = observation.effectiveDateTime;

    JsonObject valueQuantity = doc["valueQuantity"].to<JsonObject>();
    valueQuantity["value"] = observation.valueQuantity.value;
    valueQuantity["unit"] = observation.valueQuantity.unit;
    valueQuantity["system"] = OBSERVATION_QUANTITY_SYSTEM;
    valueQuantity["code"] = observation.valueQuantity.code;

    String output;
    doc.shrinkToFit();  // optional
    serializeJson(doc, output);
    return output;
}

String convertBatch(std::list<Observation> observations) {
    JsonDocument doc;

    doc["resourceType"] = "Bundle";
    doc["type"] = "transaction";

    JsonArray entries = doc["entry"].to<JsonArray>();

    for(auto observation : observations) {
        JsonObject entry = entries.add<JsonObject>();
        JsonObject resource = entry["resource"].to<JsonObject>();
        resource["resourceType"] = RESOURCE_OBSERVATION;
        //resource["meta"]["profile"][0] = "http://hl7.org/fhir/us/core/StructureDefinition/us-core-head-circumference";
        resource["status"] = STATUS_PRELIMINARY;

        JsonObject subject = resource["subject"].to<JsonObject>();
        subject["reference"]  = PATIENT_ID;

        JsonObject category = resource["category"].add<JsonObject>();
        JsonObject categoryCoding = category["coding"].add<JsonObject>();
        categoryCoding["system"] = OBSERVATION_CATEGORY_SYSTEM;
        categoryCoding["code"] = OBSERVATION_CATEGORY_CODE;
        categoryCoding["display"] = OBSERVATION_CATEGORY_DYSPLAY;

        JsonObject code = resource["code"].to<JsonObject>();
        JsonObject coding = code["coding"].add<JsonObject>();
        coding["system"] = OBSERVATION_CODE_SYSTEM;
        coding["code"] = observation.code.coding->code;
        coding["display"] = observation.code.coding->display;
        code["text"] = observation.code.text;

        resource["effectiveDateTime"] = observation.effectiveDateTime;

        JsonObject valueQuantity = resource["valueQuantity"].to<JsonObject>();
        valueQuantity["value"] = observation.valueQuantity.value;
        valueQuantity["unit"] = observation.valueQuantity.unit;
        valueQuantity["system"] = OBSERVATION_QUANTITY_SYSTEM;
        valueQuantity["code"] = observation.valueQuantity.code;
        JsonObject request = entry["request"].to<JsonObject>();
        request["method"] = "POST";
        request["url"] = "Observation";

    }

    String output;
    doc.shrinkToFit();  // optional
    serializeJson(doc, output);
    return output;
}

