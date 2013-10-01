// This file is auto-generated from clustering.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "../framework.hpp"
#include "clustering_server.hpp"
#include "clustering_serv.hpp"

namespace jubatus {
namespace server {

class clustering_impl_ : public clustering<clustering_impl_> {
 public:
  explicit clustering_impl_(const jubatus::framework::server_argv& a):
    clustering<clustering_impl_>(a.timeout),
    p_(new jubatus::framework::server_helper<clustering_serv>(a, false)) {
  }
  std::string get_config(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_config();
  }
  
  bool push(std::string name, std::vector<datum> points) {
    JWLOCK__(p_);
    return get_p()->push(points);
  }
  
  uint32_t get_revision(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_revision();
  }
  
  std::vector<std::vector<std::pair<double, datum> > > get_core_members(
      std::string name) {
    JRLOCK__(p_);
    return get_p()->get_core_members();
  }
  
  std::vector<datum> get_k_center(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_k_center();
  }
  
  datum get_nearest_center(std::string name, datum point) {
    JRLOCK__(p_);
    return get_p()->get_nearest_center(point);
  }
  
  std::vector<std::pair<double, datum> > get_nearest_members(std::string name,
       datum point) {
    JRLOCK__(p_);
    return get_p()->get_nearest_members(point);
  }
  
  bool save(std::string name, std::string id) {
    JWLOCK__(p_);
    return get_p()->save(id);
  }
  
  bool load(std::string name, std::string id) {
    JWLOCK__(p_);
    return get_p()->load(id);
  }
  
  std::map<std::string, std::map<std::string, std::string> > get_status(
      std::string name) {
    JRLOCK__(p_);
    return p_->get_status();
  }
  int run() { return p_->start(*this); }
  common::cshared_ptr<clustering_serv> get_p() { return p_->server(); }

 private:
  common::cshared_ptr<jubatus::framework::server_helper<clustering_serv> > p_;
};

}  // namespace server
}  // namespace jubatus

int main(int argc, char* argv[]) {
  return
    jubatus::framework::run_server<jubatus::server::clustering_impl_>
      (argc, argv, "clustering");
}
