
#include "nlohmann/json.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

#define file_open(var, filename, mode) \
  var.open(filename, mode);            \
  if (!var.is_open()) {                \
    perror("file open");               \
    exit(1);                           \
  }

#define json_open(var, file)             \
  var = json::parse(file);               \
  if (var == json::value_t::discarded) { \
    cout << "error parse json\n";        \
    exit(1);                             \
  }

#define json_check(json_var, val)        \
  if (!json_var.contains(val)) {         \
    cout << "error get value in json\n"; \
    exit(1);                             \
  }

unordered_map<size_t, string> json_parse_values(json& values)
{
  size_t i;
  unordered_map<size_t, string> ret;
  for (i = 0; i < values.size(); i++) {
    ret.insert({ (size_t)values[i]["id"], string(values[i]["value"]) });
  }
  return ret;
}

void json_parse_recr(json& tests, unordered_map<size_t, string>& map_values)
{
  size_t i;
  size_t size = tests.size();
  for (i = 0; i < size; i++) {
    auto jfind = map_values.find((size_t)tests[i]["id"]);
    if (jfind != map_values.end()) {
      if (tests[i].contains("value"))
        tests[i]["value"] = jfind->second;
    }
    if (tests[i].contains("values"))
      json_parse_recr(tests[i]["values"], map_values);
  }
}

int main(int argc, char* argv[])
{
  ifstream tf, vf;
  ofstream rf;
  json _tests, tests, _values, values;
  string tests_val = "tests";
  string values_val = "values";
  string tf_name;
  string vf_name;
  string rf_name;

  cin >> vf_name;
  cin >> tf_name;
  cin >> rf_name;

  file_open(tf, tf_name, ifstream::in);
  file_open(vf, vf_name, ifstream::in);
  file_open(rf, rf_name, ofstream::out);

  json_open(_tests, tf);
  json_open(_values, vf);

  json_check(_tests, tests_val);
  tests = _tests[tests_val];
  json_check(_values, values_val);
  values = _values[values_val];

  unordered_map<size_t, string> map_values = json_parse_values(values);
  json_parse_recr(tests, map_values);

  rf << tests;
  rf.close();

  return 0;
}
