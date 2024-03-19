#ifndef URL_BUILDER
#define URL_BUILDER

#include <iostream>
#include <vector>
#include <map>

using std::string;
using list = std::vector<std::string>;
using pairs = std::map<std::string, std::string>;

string formatPair(string key, string value);
string formatPairs(bool query, pairs params);

class url final {
  private:
    const list paths;
    const pairs queries;
    const string baseUrl;
  public:
    class builder {
      friend url;
      private:
          pairs queries;
          list paths;
          string baseUrl;
      public:
          builder& setBaseUrl(const string& baseUrl);
          builder& addQuery(const string&, const string&);
          builder& addPath(const string&);
          url& build() const;
    };
    explicit url(const url::builder&);
    string toString();
};

using builder = url::builder;

inline builder& builder::setBaseUrl(const string& baseUrl) {
  this->baseUrl = baseUrl;
  return *this;
}

inline builder& builder::addQuery(const string& key, const string& value) {
  queries.insert(std::pair<string, string>(key, value));
  return *this;
}

inline builder& builder::addPath(const string& path) {
  paths.push_back(path);
  return *this;
}

inline url& builder::build() const {
  return *(new url(*this));
}

inline url::url(const builder& object)
    : paths(object.paths), queries(object.queries), baseUrl(object.baseUrl){}

inline string url::toString() {
  string finalUrl = baseUrl;
  for (string path : paths) {
    finalUrl.append("/");
    finalUrl.append(path);
  }
  return finalUrl.append(formatPairs(true, queries));
};

#endif