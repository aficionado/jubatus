#ifndef JUBATUS_CLIENT_COMMON_CLIENT_HPP_
#define JUBATUS_CLIENT_COMMON_CLIENT_HPP_

#include <map>
#include <string>
#include <stdint.h>
#include <jubatus/msgpack/rpc/client.h>

namespace jubatus {
namespace client {
namespace common {

class client {
 public:
  client(const std::string& host,
         uint64_t port,
         const std::string& name,
         unsigned int timeout_sec)
      : c_(host, port), name_(name) {
    c_.set_timeout(timeout_sec);
  }

  msgpack::rpc::client& get_client() {
    return c_;
  }

  std::string get_config() {
    msgpack::rpc::future f = c_.call("get_config", name_);
    return f.get<std::string>();
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

 protected:
  msgpack::rpc::client c_;
  std::string name_;
};

}  // namespace common
}  // namespace client
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_COMMON_CLIENT_HPP_
