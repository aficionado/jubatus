// This file is auto-generated from recommender.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_RECOMMENDER_TYPES_HPP_
#define JUBATUS_CLIENT_RECOMMENDER_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <jubatus/client/datum.hpp>
#include <msgpack.hpp>

namespace jubatus {
namespace recommender {

struct id_with_score {
 public:
  MSGPACK_DEFINE(id, score);
  std::string id;
  float score;
};

}  // namespace recommender
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_RECOMMENDER_TYPES_HPP_
