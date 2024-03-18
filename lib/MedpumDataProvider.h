#ifndef MEDPLUM_DATA_PROVIDER
#define MEDPLUM_DATA_PROVIDER

#include <mutex>

extern String token;
extern std::mutex mutexToken;

void getAccessToken();


#endif