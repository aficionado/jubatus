// This file is auto-generated from anomaly.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_SERVER_SERVER_ANOMALY_CLIENT_HPP_
#define JUBATUS_SERVER_SERVER_ANOMALY_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include "jubatus/core/fv_converter/datum.hpp"
#include "anomaly_types.hpp"

namespace jubatus {
namespace client {

class anomaly {
 public:
  anomaly(const std::string& host, uint64_t port, const std::string& name,
       unsigned int timeout_sec)
      : c_(host, port) {
    c_.set_timeout(timeout_sec);
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config");
    return f.get<std::string>();
  }

  bool clear_row(const std::string& id) {
    msgpack::rpc::future f = c_.call("clear_row", id);
    return f.get<bool>();
  }

  id_with_score add(const jubatus::core::fv_converter::datum& row) {
    msgpack::rpc::future f = c_.call("add", row);
    return f.get<id_with_score>();
  }

  float update(const std::string& id,
       const jubatus::core::fv_converter::datum& row) {
    msgpack::rpc::future f = c_.call("update", id, row);
    return f.get<float>();
  }

  float overwrite(const std::string& id,
       const jubatus::core::fv_converter::datum& row) {
    msgpack::rpc::future f = c_.call("overwrite", id, row);
    return f.get<float>();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear");
    return f.get<bool>();
  }

  float calc_score(const jubatus::core::fv_converter::datum& row) {
    msgpack::rpc::future f = c_.call("calc_score", row);
    return f.get<float>();
  }

  std::vector<std::string> get_all_rows() {
    msgpack::rpc::future f = c_.call("get_all_rows");
    return f.get<std::vector<std::string> >();
  }

  bool save(const std::string& id) {
    msgpack::rpc::future f = c_.call("save", id);
    return f.get<bool>();
  }

  bool load(const std::string& id) {
    msgpack::rpc::future f = c_.call("load", id);
    return f.get<bool>();
  }

  std::map<std::string, std::map<std::string, std::string> > get_status() {
    msgpack::rpc::future f = c_.call("get_status");
    return f.get<std::map<std::string, std::map<std::string, std::string> > >();
  }

  msgpack::rpc::client& get_client() {
    return c_;
  }

 private:
  msgpack::rpc::client c_;
};

}  // namespace client
}  // namespace jubatus

#endif  // JUBATUS_SERVER_SERVER_ANOMALY_CLIENT_HPP_
