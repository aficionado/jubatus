#ifndef JUBATUS_CLIENT_DATUM_HPP_
#define JUBATUS_CLIENT_DATUM_HPP_

#include <string>
#include <vector>
#include <utility>
#include <msgpack.hpp>

namespace jubatus {
namespace common {

struct datum {
  void add_number(const std::string& key, float value) {
    num_values.push_back(std::make_pair(key, value));
  }

  void add_string(const std::string& key, const std::string& value) {
    string_values.push_back(std::make_pair(key, value));
  }

  MSGPACK_DEFINE(string_values, num_values);

  std::vector<std::pair<std::string, std::string> > string_values;
  std::vector<std::pair<std::string, double> > num_values;
};

}  // namespace common
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_DATUM_HPP_
