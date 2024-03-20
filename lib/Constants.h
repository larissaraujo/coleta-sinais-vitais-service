#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace urls {
    const static char* MEDPLUM_API_URL = "https://api.medplum.com";
}

namespace headers {
    const static char* CONTENT_TYPE = "Content-Type";
    const static char* ACCEPT = "Accept";
    const static char* ACCEPT_ENCODING = "Accept-Encoding";
    const static char* CONNECTION = "Connection";
    const static char* AUTHORIZATION = "Authorization";
}

namespace pathsParameters {
    const static char* OAUTH = "oauth2";
    const static char* AUTHORIZE = "authorize";
    const static char* TOKEN = "token";
    const static char* FHIR = "fhir";
    const static char* R4 = "R4";
    const static char* OBSERVATION = "Observation";
}

namespace queryParameters {
    const static char* CLIENT_ID = "client_id";
    const static char* CLIENT_SECRET = "client_secret";
    const static char* RESPONSE_TYPE = "response_type";
    const static char* REDIRECT_URI = "redirect_uri";
    const static char* SCOPE = "scope";
    const static char* GRANT_TYPE = "grant_type";
}

namespace parameterValues {
    const static char* CLIENT_ID = "b231c1a7-be0c-449d-b460-efa6eb99cf02";
    const static char* CLIENT_SECRET = "7c9549d9d72ae097ad5c65c3571f73ba2bd8b944d2fc9d2326faf6b2975fa1b3";
    const static char* MEDPLUM_APP = "https://app.medplum.com/";
    const static char* CODE = "code"; 
    const static char* OPENID = "openid";
    const static char* FORM_URLENCODED = "application/x-www-form-urlencoded";
    const static char* FHIR_JSON = "application/fhir+json";
    const static char* CLIENT_CREDENTIALS = "client_credentials";
}

namespace FHIR {
    const static char* OBSERVATION_CATEGORY_SYSTEM = "http://terminology.hl7.org/CodeSystem/observation-category";
    const static char* OBSERVATION_CATEGORY_CODE = "vital-signs";
    const static char* OBSERVATION_CATEGORY_DYSPLAY = "Vital Signs";
    const static char* OBSERVATION_CODE_SYSTEM = "http://loinc.org";
    const static char* OBSERVATION_QUANTITY_SYSTEM = "http://unitsofmeasure.org";
    const static char* PATIENT_ID = "Patient/c8b8a5c3-874f-4ce3-921f-d22e38d4bb09";
    const static char* RESOURCE_OBSERVATION = "Observation";
    const static char* STATUS_PRELIMINARY = "preliminary";
}

#endif

