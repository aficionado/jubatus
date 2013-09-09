// This file is auto-generated from classifier.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_CLASSIFIER_CLIENT_HPP_
#define JUBATUS_CLIENT_CLASSIFIER_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/datum.hpp>
#include "classifier_types.hpp"

namespace jubatus {
namespace classifier {
namespace client {

class classifier {
 public:
  classifier(const std::string& host, uint64_t port, const std::string& name,
       double timeout_sec)
      : c_(host, port) {
    c_.set_timeout(timeout_sec);
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config");
    return f.get<std::string>();
  }

  int32_t train(const std::vector<labeled_datum>& data) {
    msgpack::rpc::future f = c_.call("train", data);
    return f.get<int32_t>();
  }

  std::vector<std::vector<estimate_result> > classify(
      const std::vector<jubatus::core::fv_converter::datum>& data) {
    msgpack::rpc::future f = c_.call("classify", data);
    return f.get<std::vector<std::vector<estimate_result> > >();
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
}  // namespace classifier
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_CLASSIFIER_CLIENT_HPP_
