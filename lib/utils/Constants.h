#ifndef CONSTANTS_H
#define CONSTANTS_H

// Urls
#define BATCH_API_URL "https://api.medplum.com/fhir/R4"
#define OBSERVATION_API_URL "https://api.medplum.com/fhir/R4/Observation"
#define OBSERVATION_DEFINITION_API_URL "https://api.medplum.com/fhir/R4/ObservationDefinition"
#define AUTHENTICATION_API_URL "https://api.medplum.com/oauth2/token"

// Headers
#define CONTENT_TYPE "Content-Type"
#define ACCEPT "Accept"
#define ACCEPT_ENCODING "Accept-Encoding"
#define CONNECTION "Connection"
#define AUTHORIZATION "Authorization"

// Query Parameters
#define CLIENT_ID "client_id"
#define CLIENT_SECRET "client_secret"
#define GRANT_TYPE "grant_type"

// Parameter Values
#define CLIENT_ID_VALUE "35810d37-37d6-4e0c-b4aa-163300381843"
#define CLIENT_SECRET_VALUE "435fb7349ca6fe06dfa010d79e5b2ff5cde4c327b09356121e5f4b598e3b053b"
#define FORM_URLENCODED "application/x-www-form-urlencoded"
#define FHIR_JSON "application/fhir+json"
#define CLIENT_CREDENTIALS "client_credentials"

// FHIR
#define OBSERVATION_CATEGORY_SYSTEM "http://terminology.hl7.org/CodeSystem/observation-category"
#define OBSERVATION_CATEGORY_CODE "vital-signs"
#define OBSERVATION_CATEGORY_DYSPLAY "Vital Signs"
#define OBSERVATION_CODE_SYSTEM "http://loinc.org"
#define OBSERVATION_QUANTITY_SYSTEM "http://unitsofmeasure.org"
#define PATIENT_ID "Patient/a692296e-e91d-461a-acfa-90b2245e1fc2"
#define RESOURCE_OBSERVATION "Observation"
#define STATUS_PRELIMINARY "preliminary"
#define RESOURCE_COMMUNICATION "Communication"

// Vital Signs
#define TEMPERATURE_CODE "8310-5"
#define TEMPERATURE_DISPLAY "Body temperature"
#define TEMPERATURE_VALUE_CODE "Cel"
#define TEMPERATURE_UNIT "C"

#define HEART_RATE_CODE "8867-4"
#define HEART_RATE_DISPLAY "Heart Rate"
#define HEART_RATE_VALUE_CODE "/min"
#define HEART_RATE_UNIT "beats/minute"

#define OXIMETRY_CODE "2708-6"
#define OXIMETRY_DISPLAY "Oxygen saturation"
#define OXIMETRY_VALUE_CODE "%"
#define OXIMETRY_UNIT "%"

#define AUTHENTICATION_REQUEST_BODY CLIENT_ID "=" CLIENT_ID_VALUE "&" CLIENT_SECRET "=" CLIENT_SECRET_VALUE "&" GRANT_TYPE "=" CLIENT_CREDENTIALS

#endif