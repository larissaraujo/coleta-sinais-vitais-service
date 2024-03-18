#ifndef MEDPUM_ROUTES
#define MEDPUM_ROUTES

#include <../lib/Constants.h>
#include <../lib/UrlBuilder.h>

namespace oauth {
    const url AUTHORIZATION_URL = url::builder()
        .setBaseUrl(urls::MEDPLUM_API_URL)
        .addPath(pathsParameters::OAUTH)
        .addPath(pathsParameters::AUTHORIZE)
        .addQuery(queryParameters::RESPONSE_TYPE, parameterValues::CODE)
        .addQuery(queryParameters::CLIENT_ID, parameterValues::CLIENT_ID)
        .addQuery(queryParameters::REDIRECT_URI, parameterValues::MEDPLUM_APP)
        .addQuery(queryParameters::SCOPE, parameterValues::OPENID)
        .build();

    const url AUTHENTICATION_URL = url::builder()
        .setBaseUrl(urls::MEDPLUM_API_URL)
        .addPath(pathsParameters::OAUTH)
        .addPath(pathsParameters::TOKEN)
        .build();

    pairs m = {{queryParameters::CLIENT_ID, parameterValues::CLIENT_ID}, 
                                        {queryParameters::CLIENT_SECRET, parameterValues::CLIENT_SECRET}, 
                                        {queryParameters::GRANT_TYPE, parameterValues::CLIENT_CREDENTIALS}}; 
    
    const string AUTHENTICATION_BODY = formatPairs(false, m);
}

const url OBSERVATION_URL = url::builder()
        .setBaseUrl(urls::MEDPLUM_API_URL)
        .addPath(pathsParameters::FHIR)
        .addPath(pathsParameters::R4)
        .addPath(pathsParameters::OBSERVATION)
        .build();

#endif
