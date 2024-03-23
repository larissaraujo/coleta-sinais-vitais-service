#ifndef OAUTH_DATA_PROVIDER
#define OAUTH_DATA_PROVIDER

#include <mutex>

extern std::string token;
extern std::mutex mutexToken;

void getAccessToken();

#endif