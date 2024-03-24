#include <ArduinoJson.h>
#include "../lib/utils/Constants.h"
#include "../lib/fhir/ResourceModels.h"
#include <../lib/utils/JsonManager.h>

String convertBatch(std::list<Observation> observations, std::string communications) {
    JsonDocument doc;

    doc["resourceType"] = "Bundle";
    doc["type"] = "transaction";

    JsonArray entries = doc["entry"].to<JsonArray>();

    for(auto observation : observations) {
        JsonObject entry = entries.add<JsonObject>();
        JsonObject resource = entry["resource"].to<JsonObject>();
        resource["resourceType"] = RESOURCE_OBSERVATION;
        resource["status"] = STATUS_PRELIMINARY;

        JsonObject subject = resource["subject"].to<JsonObject>();
        subject["reference"] = PATIENT_ID;

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
        request["url"] = RESOURCE_OBSERVATION;
    }

    if (communications != "") {
        JsonObject entry = entries.add<JsonObject>();
        JsonObject resource = entry["resource"].to<JsonObject>();
        resource["resourceType"] = RESOURCE_COMMUNICATION;
        resource["status"] = "in-progress";

        JsonObject subject = resource["subject"].to<JsonObject>();
        subject["reference"] = PATIENT_ID;

        JsonObject category = resource["category"].add<JsonObject>();
        JsonObject categoryCoding = category["coding"].add<JsonObject>();
        categoryCoding["system"] = "http://acme.org/messagetypes";
        categoryCoding["code"] = "Alert";
        categoryCoding["display"] = "Alert";

        JsonArray payloads = resource["payload"].to<JsonArray>();
        JsonObject payload = payloads.add<JsonObject>();
        payload["contentString"] = communications;
        
        JsonObject request = entry["request"].to<JsonObject>();
        request["method"] = "POST";
        request["url"] = RESOURCE_COMMUNICATION;
    }

    String output;
    doc.shrinkToFit();  // optional
    serializeJson(doc, output);
    return output;
}

