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

#include "gmm_clustering_method.hpp"

#include <iostream>
#include <utility>
#include <vector>
#include <glog/logging.h>
#include "../../common/exception.hpp"
#include "../util/util.hpp"

using std::vector;
using std::cout;
using std::endl;

namespace jubatus {
namespace clustering {
namespace clustering_method {

gmm_clustering_method::gmm_clustering_method(size_t k)
    : k_(k) {
}

gmm_clustering_method::~gmm_clustering_method() {
}

void gmm_clustering_method::batch_update(wplist points) {
  mapper_.clear();
  gmm::eigen_wsvec_list_t data = mapper_.convert(points, true);
  gmm_.batch(data, mapper_.get_dimension(), k_);
  cout << "center[0]" << gmm_.get_centers()[0] << endl;
  kcenters_ = mapper_.revert(gmm_.get_centers());
}

void gmm_clustering_method::online_update(wplist points) {
}

std::vector<sfv_t> gmm_clustering_method::get_k_center() const {
  return kcenters_;
}

int64_t gmm_clustering_method::get_nearest_center_index(
    const sfv_t& point) const {
  return gmm_.get_nearest_center_index(mapper_.convertc(point));
}

sfv_t gmm_clustering_method::get_nearest_center(const sfv_t& point) const {
  return mapper_.revert(gmm_.get_nearest_center(mapper_.convertc(point)));
}

wplist gmm_clustering_method::get_cluster(
    size_t cluster_id,
    const wplist& points) const {
  return get_clusters(points)[cluster_id];
}

std::vector<wplist> gmm_clustering_method::get_clusters(
    const wplist& points) const {
  std::vector<wplist> ret(k_);
  for (wplist::const_iterator it = points.begin(); it != points.end(); ++it) {
    int64_t c = get_nearest_center_index(it->data);
    ret[c].push_back(*it);
  }
  return ret;
}

}  // namespace clustering_method
}  // namespace clustering
}  // namespace jubatus
