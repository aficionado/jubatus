// This file is auto-generated from nearest_neighbor.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_NEAREST_NEIGHBOR_CLIENT_HPP_
#define JUBATUS_CLIENT_NEAREST_NEIGHBOR_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/datum.hpp>
#include "nearest_neighbor_types.hpp"

namespace jubatus {
namespace nearest_neighbor {
namespace client {

class nearest_neighbor {
 public:
  nearest_neighbor(const std::string& host, uint64_t port,
       const std::string& name, unsigned int timeout_sec)
      : c_(host, port) {
    c_.set_timeout(timeout_sec);
  }

  bool init_table() {
    msgpack::rpc::future f = c_.call("init_table", name_);
    return f.get<bool>();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear", name_);
    return f.get<bool>();
  }

  bool set_row(const std::string& id, const jubatus::common::datum& d) {
    msgpack::rpc::future f = c_.call("set_row", name_, id, d);
    return f.get<bool>();
  }

  std::vector<scored_id> neighbor_row_from_id(const std::string& id,
       uint32_t size) {
    msgpack::rpc::future f = c_.call("neighbor_row_from_id", name_, id, size);
    return f.get<std::vector<scored_id> >();
  }

  std::vector<scored_id> neighbor_row_from_data(
      const jubatus::common::datum& query, uint32_t size) {
    msgpack::rpc::future f = c_.call("neighbor_row_from_data", name_, query,
         size);
    return f.get<std::vector<scored_id> >();
  }

  std::vector<scored_id> similar_row_from_id(const std::string& id,
       int32_t ret_num) {
    msgpack::rpc::future f = c_.call("similar_row_from_id", name_, id, ret_num);
    return f.get<std::vector<scored_id> >();
  }

  std::vector<scored_id> similar_row_from_data(
      const jubatus::common::datum& query, int32_t ret_num) {
    msgpack::rpc::future f = c_.call("similar_row_from_data", name_, query,
         ret_num);
    return f.get<std::vector<scored_id> >();
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

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config", name_);
    return f.get<std::string>();
  }

  msgpack::rpc::client& get_client() {
    return c_;
  }

 private:
  msgpack::rpc::client c_;
  std::string name_;
};

}  // namespace client
}  // namespace nearest_neighbor
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_NEAREST_NEIGHBOR_CLIENT_HPP_
