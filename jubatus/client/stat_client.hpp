// This file is auto-generated from stat.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_STAT_CLIENT_HPP_
#define JUBATUS_CLIENT_STAT_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/datum.hpp>
#include "stat_types.hpp"

namespace jubatus {
namespace stat {
namespace client {

class stat {
 public:
  stat(const std::string& host, uint64_t port, const std::string& name,
       double timeout_sec)
      : c_(host, port), name_(name) {
    c_.set_timeout(timeout_sec);
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config", name_);
    return f.get<std::string>();
  }

  bool push(const std::string& key, double value) {
    msgpack::rpc::future f = c_.call("push", name_, key, value);
    return f.get<bool>();
  }

  double sum(const std::string& key) {
    msgpack::rpc::future f = c_.call("sum", name_, key);
    return f.get<double>();
  }

  double stddev(const std::string& key) {
    msgpack::rpc::future f = c_.call("stddev", name_, key);
    return f.get<double>();
  }

  double max(const std::string& key) {
    msgpack::rpc::future f = c_.call("max", name_, key);
    return f.get<double>();
  }

  double min(const std::string& key) {
    msgpack::rpc::future f = c_.call("min", name_, key);
    return f.get<double>();
  }

  double entropy(const std::string& key) {
    msgpack::rpc::future f = c_.call("entropy", name_, key);
    return f.get<double>();
  }

  double moment(const std::string& key, int32_t degree, double center) {
    msgpack::rpc::future f = c_.call("moment", name_, key, degree, center);
    return f.get<double>();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear", name_);
    return f.get<bool>();
  }

  bool save(const std::string& id) {
    msgpack::rpc::future f = c_.call("save", name_, id);
    return f.get<bool>();
  }

  bool load(const std::string& id) {
    msgpack::rpc::future f = c_.call("load", name_, id);
    return f.get<bool>();
  }

  std::map<std::string, std::map<std::string, std::string> > get_status() {
    msgpack::rpc::future f = c_.call("get_status", name_);
    return f.get<std::map<std::string, std::map<std::string, std::string> > >();
  }

  msgpack::rpc::client& get_client() {
    return c_;
  }

 private:
  msgpack::rpc::client c_;
  std::string name_;
};

}  // namespace client
}  // namespace stat
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_STAT_CLIENT_HPP_
