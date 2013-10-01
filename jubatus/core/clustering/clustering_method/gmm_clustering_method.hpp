// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2012 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License version 2.1 as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef JUBATUS_CLUSTERING_CLUSTER_MANAGER_GMM_CLUSTER_MANAGER_HPP_
#define JUBATUS_CLUSTERING_CLUSTER_MANAGER_GMM_CLUSTER_MANAGER_HPP_

#include <vector>
#include "clustering_method.hpp"
#include "gmm/eigen_feature_mapper.hpp"
#include "gmm/gmm.hpp"
#include "gmm/types.hpp"

namespace jubatus {
namespace core {
namespace clustering {
namespace clustering_method {

class clustering_method_serializer;

class gmm_clustering_method : public clustering_method {
 public:
  explicit gmm_clustering_method(size_t k);
  ~gmm_clustering_method();

  void batch_update(wplist points);
  void online_update(wplist points);
  std::vector<sfv_t> get_k_center() const;
  sfv_t get_nearest_center(const sfv_t& point) const;
  int64_t get_nearest_center_index(const sfv_t& point) const;
  wplist get_cluster(size_t cluster_id, const wplist& points) const;
  std::vector<wplist> get_clusters(const wplist& points) const;

 private:
  size_t k_;
  std::vector<sfv_t> kcenters_;
  gmm::eigen_feature_mapper mapper_;
  gmm::gmm gmm_;

  friend class clustering_method_serializer;
  template <class Ar>
  void serialize(Ar &ar) {
    // TODO(akira) : serialize me
  }
};

}  // namespace clustering_method
}  // namespace clustering
}  // namespace core
}  // namespace jubatus

#endif  // JUBATUS_CLUSTERING_CLUSTER_MANAGER_KMEANS_CLUSTER_MANAGER_HPP_
