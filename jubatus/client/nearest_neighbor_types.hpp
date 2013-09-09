// This file is auto-generated from nearest_neighbor.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_NEAREST_NEIGHBOR_TYPES_HPP_
#define JUBATUS_CLIENT_NEAREST_NEIGHBOR_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <jubatus/client/datum.hpp>
#include <msgpack.hpp>

namespace jubatus {
namespace nearest_neighbor {

struct scored_id {
 public:
  MSGPACK_DEFINE(id, score);
  std::string id;
  float score;
  scored_id() {
  }
  scored_id(const std::string& id, float score)
    : id(id), score(score) {
  }
};

}  // namespace nearest_neighbor
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_NEAREST_NEIGHBOR_TYPES_HPP_
