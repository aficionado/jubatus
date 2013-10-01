// This file is auto-generated from cluster_analysis.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "../framework.hpp"
#include "cluster_analysis_server.hpp"
#include "cluster_analysis_serv.hpp"

namespace jubatus {
namespace server {

class cluster_analysis_impl_ : public cluster_analysis<cluster_analysis_impl_> {
 public:
  explicit cluster_analysis_impl_(const jubatus::framework::server_argv& a):
    cluster_analysis<cluster_analysis_impl_>(a.timeout),
    p_(new jubatus::framework::server_helper<cluster_analysis_serv>(a, false)) {
  }
  std::string get_config(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_config();
  }
  
  bool add_snapshot(std::string name, std::string clustering_name) {
    JWLOCK__(p_);
    return get_p()->add_snapshot(clustering_name);
  }
  
  std::vector<change_graph> get_history(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_history();
  }
  
  std::vector<clustering_snapshot> get_snapshots(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_snapshots();
  }
  int run() { return p_->start(*this); }
  common::cshared_ptr<cluster_analysis_serv> get_p() { return p_->server(); }

 private:
  common::cshared_ptr<jubatus::framework::server_helper<cluster_analysis_serv> > p_;
};

}  // namespace server
}  // namespace jubatus

int main(int argc, char* argv[]) {
  return
    jubatus::framework::run_server<jubatus::server::cluster_analysis_impl_>
      (argc, argv, "cluster_analysis");
}
