// This file is auto-generated from classifier.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <pficommon/lang/shared_ptr.h>

#include "../../server/framework.hpp"
#include "classifier_server.hpp"
#include "classifier_serv.hpp"

namespace jubatus {
namespace server {

class classifier_impl_ : public classifier<classifier_impl_> {
 public:
  explicit classifier_impl_(const jubatus::server::framework::server_argv& a):
    classifier<classifier_impl_>(a.timeout),
    p_(new jubatus::server::framework::server_helper<classifier_serv>(a,
        false)) {
  }
  std::string get_config(const std::string& name) {
    JRLOCK_(p_);
    return get_p()->get_config();
  }

  int32_t train(const std::string& name,
      const std::vector<std::pair<std::string,
      jubatus::core::fv_converter::datum> >& data) {
    JWLOCK_(p_);
    return get_p()->train(data);
  }

  std::vector<std::vector<estimate_result> > classify(const std::string& name,
      const std::vector<jubatus::core::fv_converter::datum>& data) {
    JRLOCK_(p_);
    return get_p()->classify(data);
  }

  bool clear(const std::string& name) {
    JWLOCK_(p_);
    return get_p()->clear();
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
  pfi::lang::shared_ptr<classifier_serv> get_p() { return p_->server(); }

 private:
  pfi::lang::shared_ptr<jubatus::server::framework::server_helper<classifier_serv> > p_;
};

}  // namespace server
}  // namespace jubatus

int main(int argc, char* argv[]) {
  return
    jubatus::server::framework::run_server<jubatus::server::classifier_impl_>
      (argc, argv, "classifier");
}
