// This file is auto-generated from cluster_analysis.idl
// *** DO NOT EDIT ***

#ifndef JUBATUS_SERVER_SERVER_CLUSTER_ANALYSIS_TYPES_HPP_
#define JUBATUS_SERVER_SERVER_CLUSTER_ANALYSIS_TYPES_HPP_

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
#include <utility>

#include <msgpack.hpp>

#include "../../core/fv_converter/datum.hpp"

namespace jubatus {

struct cluster_relation {
 public:
  MSGPACK_DEFINE(cluster1, cluster2, similarity);
  int32_t cluster1;
  int32_t cluster2;
  double similarity;
};

struct change_graph {
 public:
  MSGPACK_DEFINE(snapshot_name1, snapshot_name2, related_pairs);
  std::string snapshot_name1;
  std::string snapshot_name2;
  std::vector<cluster_relation> related_pairs;
};

struct clustering_snapshot {
 public:
  MSGPACK_DEFINE(name, clusters);
  std::string name;
  std::vector<std::vector<std::pair<double,
       jubatus::core::fv_converter::datum> > > clusters;
};

}  // namespace jubatus

#endif  // JUBATUS_SERVER_SERVER_CLUSTER_ANALYSIS_TYPES_HPP_
