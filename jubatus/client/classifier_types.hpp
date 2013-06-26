// This file is auto-generated from classifier.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_CLIENT_CLASSIFIER_TYPES_HPP_
#define JUBATUS_CLIENT_CLASSIFIER_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <jubatus/client/datum.hpp>
#include <msgpack.hpp>

namespace jubatus {
namespace classifier {

struct estimate_result {
 public:
  MSGPACK_DEFINE(label, score);
  std::string label;
  double score;
};

struct labeled_datum {
 public:
  MSGPACK_DEFINE(label, data);
  std::string label;
  jubatus::common::datum data;
};

}  // namespace classifier
}  // namespace jubatus

#endif  // JUBATUS_CLIENT_CLASSIFIER_TYPES_HPP_
