#include <../lib/UrlBuilder.h>

string formatPair(string key, string value) {
  return key.append("=").append(value);
}

string formatPairs(bool query, pairs params) {
  auto it = params.begin();
  if (it != params.end()) {
    string formatted = query ? "?" : "";
    formatted.append(formatPair(it->first, it->second));
    for(it++; it != params.end(); it++) {
      formatted.append("&");
      formatted.append(formatPair(it->first, it->second));
    }
    return formatted;
  }
  return "";
}