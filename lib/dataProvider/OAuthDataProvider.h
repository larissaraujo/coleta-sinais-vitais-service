#ifndef OAUTH_DATA_PROVIDER
#define OAUTH_DATA_PROVIDER

extern std::string token;
extern SemaphoreHandle_t xSemaphoreToken;

void getAccessToken();

#endif