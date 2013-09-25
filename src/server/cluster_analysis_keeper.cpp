// This file is auto-generated from cluster_analysis.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <glog/logging.h>

#include "../common/exception.hpp"
#include "../framework/aggregators.hpp"
#include "../framework/keeper.hpp"
#include "cluster_analysis_types.hpp"

namespace jubatus {

int run_keeper(int argc, char* argv[]) {
  try {
    jubatus::framework::keeper k(
        jubatus::framework::keeper_argv(argc, argv, "cluster_analysis"));
    k.register_async_random<std::string>("get_config");
    k.register_async_broadcast<bool, std::string>("add_snapshot",
         pfi::lang::function<bool(bool, bool)>(&jubatus::framework::all_and));
    k.register_async_random<std::vector<change_graph> >("get_history");
    k.register_async_random<std::vector<clustering_snapshot> >("get_snapshots");
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
