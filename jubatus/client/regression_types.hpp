// This file is auto-generated from regression.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_REGRESSION_TYPES_HPP_
#define JUBATUS_CLIENT_REGRESSION_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <jubatus/client/datum.hpp>
#include <msgpack.hpp>

namespace jubatus {
namespace regression {

struct scored_datum {
 public:
  MSGPACK_DEFINE(score, data);
  float score;
  jubatus::common::datum data;
};

}  // namespace regression
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_REGRESSION_TYPES_HPP_
