// This file is auto-generated from clustering.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <glog/logging.h>

#include "../common/exception.hpp"
#include "../framework/aggregators.hpp"
#include "../framework/keeper.hpp"
#include "clustering_types.hpp"

namespace jubatus {

int run_keeper(int argc, char* argv[]) {
  try {
    jubatus::framework::keeper k(
        jubatus::framework::keeper_argv(argc, argv, "clustering"));
    k.register_async_random<std::string>("get_config");
    k.register_async_random<bool, std::vector<datum> >("push");
    k.register_async_random<uint32_t>("get_revision");
    k.register_async_random<std::vector<std::vector<std::pair<double,
         datum> > > >("get_core_members");
    k.register_async_random<std::vector<datum> >("get_k_center");
    k.register_async_random<datum, datum>("get_nearest_center");
    k.register_async_random<std::vector<std::pair<double, datum> >, datum>(
        "get_nearest_members");
    k.register_async_broadcast<bool, std::string>("save",
         pfi::lang::function<bool(bool, bool)>(&jubatus::framework::all_and));
    k.register_async_broadcast<bool, std::string>("load",
         pfi::lang::function<bool(bool, bool)>(&jubatus::framework::all_and));
    k.register_async_broadcast<std::map<std::string, std::map<std::string,
         std::string> > >("get_status",
         pfi::lang::function<std::map<std::string, std::map<std::string,
         std::string> >(std::map<std::string, std::map<std::string,
         std::string> >, std::map<std::string, std::map<std::string,
         std::string> >)>(&jubatus::framework::merge<std::string,
         std::map<std::string, std::string> >));
    return k.run();
  } catch (const jubatus::exception::jubatus_exception& e) {
    LOG(FATAL) << e.diagnostic_information(true);
    return -1;
  }
}

}  // namespace jubatus

int main(int argc, char* argv[]) {
  jubatus::run_keeper(argc, argv);
}
