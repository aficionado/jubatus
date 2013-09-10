// This file is auto-generated from anomaly.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_ANOMALY_CLIENT_HPP_
#define JUBATUS_CLIENT_ANOMALY_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/common/datum.hpp>
#include "anomaly_types.hpp"

namespace jubatus {
namespace anomaly {
namespace client {

class anomaly {
 public:
  anomaly(const std::string& host, uint64_t port, const std::string& name,
       double timeout_sec)
      : c_(host, port), name_(name) {
    c_.set_timeout(timeout_sec);
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config", name_);
    return f.get<std::string>();
  }

  bool clear_row(const std::string& id) {
    msgpack::rpc::future f = c_.call("clear_row", name_, id);
    return f.get<bool>();
  }

  id_with_score add(const jubatus::client::common::datum& row) {
    msgpack::rpc::future f = c_.call("add", name_, row);
    return f.get<id_with_score>();
  }

  float update(const std::string& id,
       const jubatus::client::common::datum& row) {
    msgpack::rpc::future f = c_.call("update", name_, id, row);
    return f.get<float>();
  }

  float overwrite(const std::string& id,
       const jubatus::client::common::datum& row) {
    msgpack::rpc::future f = c_.call("overwrite", name_, id, row);
    return f.get<float>();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear", name_);
    return f.get<bool>();
  }

  float calc_score(const jubatus::client::common::datum& row) {
    msgpack::rpc::future f = c_.call("calc_score", name_, row);
    return f.get<float>();
  }

  std::vector<std::string> get_all_rows() {
    msgpack::rpc::future f = c_.call("get_all_rows", name_);
    return f.get<std::vector<std::string> >();
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
}  // namespace anomaly
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_ANOMALY_CLIENT_HPP_
