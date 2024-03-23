#ifndef CONSTANTS_H
#define CONSTANTS_H

// Urls
#define MEDPLUM_API_URL "https://api.medplum.com"
#define BATCH_API_URL "https://api.medplum.com/fhir/R4"
#define OBSERVATION_API_URL "https://api.medplum.com/fhir/R4/Observation"
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
#define RESPONSE_TYPE "response_type"
#define REDIRECT_URI "redirect_uri"
#define SCOPE "scope"
#define GRANT_TYPE "grant_type"

// Parameter Values
#define CLIENT_ID_VALUE "b231c1a7-be0c-449d-b460-efa6eb99cf02"
#define CLIENT_SECRET_VALUE "7c9549d9d72ae097ad5c65c3571f73ba2bd8b944d2fc9d2326faf6b2975fa1b3"
#define MEDPLUM_APP "https://app.medplum.com/"
#define CODE "code"
#define OPENID "openid"
#define FORM_URLENCODED "application/x-www-form-urlencoded"
#define FHIR_JSON "application/fhir+json"
#define CLIENT_CREDENTIALS "client_credentials"

// FHIR
#define OBSERVATION_CATEGORY_SYSTEM "http://terminology.hl7.org/CodeSystem/observation-category"
#define OBSERVATION_CATEGORY_CODE "vital-signs"
#define OBSERVATION_CATEGORY_DYSPLAY "Vital Signs"
#define OBSERVATION_CODE_SYSTEM "http://loinc.org"
#define OBSERVATION_QUANTITY_SYSTEM "http://unitsofmeasure.org"
#define PATIENT_ID "Patient/c8b8a5c3-874f-4ce3-921f-d22e38d4bb09"
#define RESOURCE_OBSERVATION "Observation"
#define STATUS_PRELIMINARY "preliminary"

// Vital Signs
#define TEMPERATURE_CODE "8310-5"
#define TEMPERATURE_DISPLAY "Body temperature"
#define TEMPERATURE_VALUE_CODE "Cel"
#define TEMPERATURE_UNIT "C"
#define TEMPERATURE_LOW 35
#define TEMPERATURE_HIGH 37.8

#define HEART_RATE_CODE "8867-4"
#define HEART_RATE_DISPLAY "Heart Rate"
#define HEART_RATE_VALUE_CODE "/min"
#define HEART_RATE_UNIT "beats/minute"
#define HEART_RATE_LOW 50
#define HEART_RATE_HIGH 100

#define OXIMETRY_CODE "2708-6"
#define OXIMETRY_DISPLAY "Oxygen saturation"
#define OXIMETRY_VALUE_CODE "%"
#define OXIMETRY_UNIT "%"
#define HEART_RATE_LOW 90

#define AUTHENTICATION_REQUEST_BODY CLIENT_ID "=" CLIENT_ID_VALUE "&" CLIENT_SECRET "=" CLIENT_SECRET_VALUE "&" GRANT_TYPE "=" CLIENT_CREDENTIALS

#endif