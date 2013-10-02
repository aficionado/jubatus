// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2012,2013 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
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
#include <utility>
#include <vector>
#include <pficommon/lang/bind.h>
#include "../common/vector_util.hpp"
#include "../fv_converter/revert.hpp"

namespace jubatus {
namespace core {
namespace driver {

clustering::clustering(
    core::clustering::clustering* clustering_method,
    pfi::lang::shared_ptr<server::framework::mixer::mixer> mixer,
    pfi::lang::shared_ptr<fv_converter::datum_to_fv_converter> converter)
    : mixer_(mixer),
      mixable_holder_(new framework::mixable_holder),
      converter_(converter) {
  clustering_->set_model(mixable_clustering::model_ptr(clustering_method));
  wm_->set_model
      (pfi::lang::shared_ptr<fv_converter::weight_manager>(
          new fv_converter::weight_manager));

  mixer_->set_mixable_holder(mixable_holder_);
  mixable_holder_->register_mixable(clustering_);
  mixable_holder_->register_mixable(wm_);

  converter_->set_weight_manager(wm_->get_model());
}

clustering::~clustering() {
}

void clustering::push(const std::vector<fv_converter::datum>& points) {
  clustering_->get_model()->push(to_weighted_point_vector(points));
}

fv_converter::datum clustering::get_nearest_center(const fv_converter::datum& point) const {
  return to_datum(
      clustering_->get_model()->get_nearest_center(to_sfv_const(point)));
}

std::vector<std::pair<double, fv_converter::datum> > clustering::get_nearest_members(
  const fv_converter::datum& point) const {
  return to_weighted_datum_vector(
      clustering_->get_model()->get_nearest_members(to_sfv_const(point)));
}

std::vector<fv_converter::datum> clustering::get_k_center() const {
  return to_datum_vector(clustering_->get_model()->get_k_center());
}

std::vector<std::vector<std::pair<double, fv_converter::datum> > >
clustering::get_core_members() const {
  std::vector<std::vector<core::clustering::weighted_point> > src =
      clustering_->get_model()->get_core_members();

  std::vector<std::vector<std::pair<double, fv_converter::datum> > >  ret;
  ret.reserve(src.size());
  std::transform(
      src.begin(), src.end(), std::back_inserter(ret), pfi::lang::bind(
          &clustering::to_weighted_datum_vector, this, pfi::lang::_1));

  return ret;
}

size_t clustering::get_revision() const {
  return clustering_->get_model()->get_revision();
}

// private

common::sfv_t clustering::to_sfv(const fv_converter::datum& dat) {
  common::sfv_t ret;
  converter_->convert_and_update_weight(dat, ret);
  sort_and_merge(ret);
  return ret;
}

common::sfv_t clustering::to_sfv_const(const fv_converter::datum& dat) const {
  common::sfv_t ret;
  converter_->convert(dat, ret);
  sort_and_merge(ret);
  return ret;
}

fv_converter::datum clustering::to_datum(const common::sfv_t& src) const {
  fv_converter::datum ret;
  fv_converter::revert_feature(src, ret);
  return ret;
}

weighted_point core::clustering::to_weighted_point(const fv_converter::datum& src) {
  weighted_point ret;
  ret.data = to_sfv(src);
  ret.weight = 1;
  ret.free_long = 1;
  ret.free_double = 1;
  ret.original = src;
  return ret;
}

std::pair<double, fv_converter::datum> clustering::to_weighted_datum(
    const core::clustering::weighted_point& src) const {
  return std::make_pair(src.weight, src.original);
}

std::vector<fv_converter::datum> clustering::to_datum_vector(
    const std::vector<common::sfv_t>& src) const {
  std::vector<fv_converter::datum> ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_datum, this, pfi::lang::_1));
  return ret;
}

std::vector<core::clustering::weighted_point> clustering::to_weighted_point_vector(
  const std::vector<fv_converter::datum>& src) {
  std::vector<core::clustering::weighted_point> ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_weighted_point, this, pfi::lang::_1));
  return ret;
}

std::vector<std::pair<double, fv_converter::datum> > clustering::to_weighted_datum_vector(
    const std::vector<core::clustering::weighted_point>& src) const {
  std::vector<std::pair<double, fv_converter::datum> > ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_weighted_datum, this, pfi::lang::_1));
  return ret;
}

}  // namespace driver
}  // namespace core
}  // namespace jubatus
