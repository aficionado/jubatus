// This file is auto-generated from anomaly.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <pficommon/lang/shared_ptr.h>

#include "../../server/framework.hpp"
#include "anomaly_server.hpp"
#include "anomaly_serv.hpp"

namespace jubatus {
namespace server {

class anomaly_impl_ : public anomaly<anomaly_impl_> {
 public:
  explicit anomaly_impl_(const jubatus::server::framework::server_argv& a):
    anomaly<anomaly_impl_>(a.timeout),
    p_(new jubatus::server::framework::server_helper<anomaly_serv>(a, true)) {
  }
  std::string get_config(const std::string& name) {
    JRLOCK_(p_);
    return get_p()->get_config();
  }

  bool clear_row(const std::string& name, const std::string& id) {
    JWLOCK_(p_);
    return get_p()->clear_row(id);
  }

  std::pair<std::string, float> add(const std::string& name,
      const jubatus::core::fv_converter::datum& row) {
    NOLOCK_(p_);
    return get_p()->add(row);
  }

  float update(const std::string& name, const std::string& id,
      const jubatus::core::fv_converter::datum& row) {
    JWLOCK_(p_);
    return get_p()->update(id, row);
  }

  float overwrite(const std::string& name, const std::string& id,
      const jubatus::core::fv_converter::datum& row) {
    JWLOCK_(p_);
    return get_p()->overwrite(id, row);
  }

  bool clear(const std::string& name) {
    JWLOCK_(p_);
    return get_p()->clear();
  }

  float calc_score(const std::string& name,
      const jubatus::core::fv_converter::datum& row) {
    JRLOCK_(p_);
    return get_p()->calc_score(row);
  }

  std::vector<std::string> get_all_rows(const std::string& name) {
    JRLOCK_(p_);
    return get_p()->get_all_rows();
  }

  bool save(const std::string& name, const std::string& id) {
    JWLOCK_(p_);
    return get_p()->save(id);
  }

  bool load(const std::string& name, const std::string& id) {
    JWLOCK_(p_);
    return get_p()->load(id);
  }

  std::map<std::string, std::map<std::string, std::string> > get_status(
      const std::string& name) {
    JRLOCK_(p_);
    return p_->get_status();
  }
  int run() { return p_->start(*this); }
  pfi::lang::shared_ptr<anomaly_serv> get_p() { return p_->server(); }

 private:
  pfi::lang::shared_ptr<jubatus::server::framework::server_helper<anomaly_serv> > p_;
};

}  // namespace server
}  // namespace jubatus

int main(int argc, char* argv[]) {
  return
    jubatus::server::framework::run_server<jubatus::server::anomaly_impl_>
      (argc, argv, "anomaly");
}
