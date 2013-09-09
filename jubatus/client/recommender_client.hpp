// This file is auto-generated from recommender.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_RECOMMENDER_CLIENT_HPP_
#define JUBATUS_CLIENT_RECOMMENDER_CLIENT_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <jubatus/msgpack/rpc/client.h>
#include <jubatus/client/datum.hpp>
#include "recommender_types.hpp"

namespace jubatus {
namespace recommender {
namespace client {

class recommender {
 public:
  recommender(const std::string& host, uint64_t port, const std::string& name,
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

  bool update_row(const std::string& id, const jubatus::common::datum& row) {
    msgpack::rpc::future f = c_.call("update_row", name_, id, row);
    return f.get<bool>();
  }

  bool clear() {
    msgpack::rpc::future f = c_.call("clear", name_);
    return f.get<bool>();
  }

  jubatus::common::datum complete_row_from_id(const std::string& id) {
    msgpack::rpc::future f = c_.call("complete_row_from_id", name_, id);
    return f.get<jubatus::common::datum>();
  }

  jubatus::common::datum complete_row_from_datum(
      const jubatus::common::datum& row) {
    msgpack::rpc::future f = c_.call("complete_row_from_datum", name_, row);
    return f.get<jubatus::common::datum>();
  }

  std::vector<id_with_score> similar_row_from_id(const std::string& id,
       uint32_t size) {
    msgpack::rpc::future f = c_.call("similar_row_from_id", name_, id, size);
    return f.get<std::vector<id_with_score> >();
  }

  std::vector<id_with_score> similar_row_from_datum(
      const jubatus::common::datum& row, uint32_t size) {
    msgpack::rpc::future f = c_.call("similar_row_from_datum", name_, row,
         size);
    return f.get<std::vector<id_with_score> >();
  }

  jubatus::common::datum decode_row(const std::string& id) {
    msgpack::rpc::future f = c_.call("decode_row", name_, id);
    return f.get<jubatus::common::datum>();
  }

  std::vector<std::string> get_all_rows() {
    msgpack::rpc::future f = c_.call("get_all_rows", name_);
    return f.get<std::vector<std::string> >();
  }

  float calc_similarity(const jubatus::common::datum& lhs,
       const jubatus::common::datum& rhs) {
    msgpack::rpc::future f = c_.call("calc_similarity", name_, lhs, rhs);
    return f.get<float>();
  }

  float calc_l2norm(const jubatus::common::datum& row) {
    msgpack::rpc::future f = c_.call("calc_l2norm", name_, row);
    return f.get<float>();
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
}  // namespace recommender
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_RECOMMENDER_CLIENT_HPP_
