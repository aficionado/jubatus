// This file is auto-generated from regression.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_SERVER_SERVER_REGRESSION_SERVER_HPP_
#define JUBATUS_SERVER_SERVER_REGRESSION_SERVER_HPP_

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <pficommon/lang/bind.h>

#include "../../server/common/mprpc/rpc_server.hpp"
#include "regression_types.hpp"

namespace jubatus {
namespace server {

template <class Impl>
class regression : public jubatus::server::common::mprpc::rpc_server {
 public:
  explicit regression(double timeout_sec) : rpc_server(timeout_sec) {
    Impl* impl = static_cast<Impl*>(this);
    rpc_server::add<std::string()>("get_config", pfi::lang::bind(
        &Impl::get_config, impl));
    rpc_server::add<int32_t(std::vector<scored_datum>)>("train",
         pfi::lang::bind(&Impl::train, impl, pfi::lang::_1));
    rpc_server::add<std::vector<float>(
        std::vector<jubatus::core::fv_converter::datum>)>("estimate",
         pfi::lang::bind(&Impl::estimate, impl, pfi::lang::_1));
    rpc_server::add<bool()>("clear", pfi::lang::bind(&Impl::clear, impl));
    rpc_server::add<bool(std::string)>("save", pfi::lang::bind(&Impl::save,
         impl, pfi::lang::_1));
    rpc_server::add<bool(std::string)>("load", pfi::lang::bind(&Impl::load,
         impl, pfi::lang::_1));
    rpc_server::add<std::map<std::string, std::map<std::string, std::string> >(
        )>("get_status", pfi::lang::bind(&Impl::get_status, impl));
  }
};

}  // namespace server
}  // namespace jubatus

#endif  // JUBATUS_SERVER_SERVER_REGRESSION_SERVER_HPP_
