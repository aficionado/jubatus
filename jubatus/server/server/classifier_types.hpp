// This file is auto-generated from classifier.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_SERVER_SERVER_CLASSIFIER_TYPES_HPP_
#define JUBATUS_SERVER_SERVER_CLASSIFIER_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "jubatus/core/fv_converter/datum.hpp"
#include <msgpack.hpp>

namespace jubatus {

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
  jubatus::core::fv_converter::datum data;
};

}  // namespace jubatus

#endif  // JUBATUS_SERVER_SERVER_CLASSIFIER_TYPES_HPP_
