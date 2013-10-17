// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2013 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
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

#include "clustering.hpp"

#include <algorithm>
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include <pficommon/data/serialization.h>
#include <pficommon/lang/function.h>
#include <pficommon/lang/bind.h>

#include "../common/jsonconfig.hpp"
#include "clustering_method_factory.hpp"
#include "storage_factory.hpp"

using pfi::lang::shared_ptr;

namespace jubatus {
namespace core {
namespace clustering {

clustering::clustering(
    const std::string& name,
    const std::string& method,
    const clustering_config& cfg)
    : config_(cfg),
      name_(name),
      method_(method),
      storage_(new mixable_storage) {
  init();
}

clustering::~clustering() {
}

void clustering::init() {
  set_storage(storage_factory::create(name_, config_));
  set_clustering_method(
      clustering_method::clustering_method_factory::create(method_, config_));
}

void clustering::set_storage(shared_ptr<storage> storage) {
  storage->add_event_listener(REVISION_CHANGE,
      pfi::lang::bind(&clustering::update_clusters, this, pfi::lang::_1, true));
  storage->add_event_listener(UPDATE,
      pfi::lang::bind(&clustering::update_clusters,
          this, pfi::lang::_1, false));
  storage_->set_model(storage);
}

pfi::lang::shared_ptr<storage> clustering::get_storage() {
  return storage_->get_model();
}

void clustering::update_clusters(const wplist& points, bool batch) {
  if (batch) {
    clustering_method_->batch_update(points);
  } else {
    clustering_method_->online_update(points);
  }
}

void clustering::set_clustering_method(
    shared_ptr<clustering_method::clustering_method> clustering_method) {
  clustering_method_ = clustering_method;
}

bool clustering::push(const std::vector<weighted_point>& points) {
  pfi::lang::shared_ptr<storage> sto = storage_->get_model();
  for (std::vector<weighted_point>::const_iterator it = points.begin();
       it != points.end(); ++it) {
    sto->add(*it);
  }
  return true;
}

wplist clustering::get_coreset() const {
  return storage_->get_model()->get_all();
}

std::vector<common::sfv_t> clustering::get_k_center() const {
  return clustering_method_->get_k_center();
}

common::sfv_t clustering::get_nearest_center(const common::sfv_t& point) const {
  return clustering_method_->get_nearest_center(point);
}

wplist clustering::get_nearest_members(const common::sfv_t& point) const {
  int64_t clustering_id = clustering_method_->get_nearest_center_index(point);
  if (clustering_id == -1) {
    return wplist();
  }
  return clustering_method_->get_cluster(clustering_id, get_coreset());
}

std::vector<wplist> clustering::get_core_members() const {
  return clustering_method_->get_clusters(get_coreset());
}

size_t clustering::get_revision() const {
  return storage_->get_model()->get_revision();
}

void clustering::register_mixables_to_holder(
    framework::mixable_holder& mixable_holder) {
  mixable_holder.register_mixable(storage_);
}

std::string clustering::type() const {
  return "clustering";
}

}  // namespace clustering
}  // namespace core
}  // namespace jubatus
