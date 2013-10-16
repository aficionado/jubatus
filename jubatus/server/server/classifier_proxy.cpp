// This file is auto-generated from classifier.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <glog/logging.h>

#include "jubatus/core/common/exception.hpp"
#include "../../server/framework/aggregators.hpp"
#include "../../server/framework/proxy.hpp"
#include "classifier_types.hpp"

namespace jubatus {

int run_proxy(int argc, char* argv[]) {
  try {
    jubatus::server::framework::proxy k(
        jubatus::server::framework::proxy_argv(argc, argv, "classifier"));
    k.register_async_random<std::string>("get_config");
    k.register_async_random<int32_t, std::vector<std::pair<std::string,
        jubatus::core::fv_converter::datum> > >("train");
    k.register_async_random<std::vector<std::vector<estimate_result> >,
        std::vector<jubatus::core::fv_converter::datum> >("classify");
    k.register_async_broadcast<bool>("clear", pfi::lang::function<bool(bool,
        bool)>(&jubatus::server::framework::all_and));
    k.register_async_broadcast<bool, std::string>("save",
        pfi::lang::function<bool(bool, bool)>(
        &jubatus::server::framework::all_and));
    k.register_async_broadcast<bool, std::string>("load",
        pfi::lang::function<bool(bool, bool)>(
        &jubatus::server::framework::all_and));
    k.register_async_broadcast<std::map<std::string, std::map<std::string,
        std::string> > >("get_status", pfi::lang::function<std::map<std::string,
        std::map<std::string, std::string> >(std::map<std::string,
        std::map<std::string, std::string> >, std::map<std::string,
        std::map<std::string, std::string> >)>(
        &jubatus::server::framework::merge<std::string, std::map<std::string,
        std::string> >));
    return k.run();
  } catch (const jubatus::core::common::exception::jubatus_exception& e) {
    LOG(FATAL) << e.diagnostic_information(true);
    return -1;
  }
}

}  // namespace jubatus

int main(int argc, char* argv[]) {
  jubatus::run_proxy(argc, argv);
}
