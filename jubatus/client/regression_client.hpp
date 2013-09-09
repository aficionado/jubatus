// This file is auto-generated from regression.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_REGRESSION_CLIENT_HPP_
#define JUBATUS_CLIENT_REGRESSION_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/datum.hpp>
#include "regression_types.hpp"

namespace jubatus {
namespace regression {
namespace client {

class regression {
 public:
  regression(const std::string& host, uint64_t port, const std::string& name,
       double timeout_sec)
      : c_(host, port) {
    c_.set_timeout(timeout_sec);
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config");
    return f.get<std::string>();
  }

  int32_t train(const std::vector<scored_datum>& train_data) {
    msgpack::rpc::future f = c_.call("train", train_data);
    return f.get<int32_t>();
  }

  std::vector<float> estimate(
      const std::vector<jubatus::core::fv_converter::datum>& estimate_data) {
    msgpack::rpc::future f = c_.call("estimate", estimate_data);
    return f.get<std::vector<float> >();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear");
    return f.get<bool>();
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
}  // namespace regression
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_REGRESSION_CLIENT_HPP_
