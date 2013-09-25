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
#include "../common/shared_ptr.hpp"
#include "../common/vector_util.hpp"
#include "../fv_converter/revert.hpp"

namespace jubatus {
namespace driver {

clustering::clustering(
    jubatus::clustering::clustering* clustering_method,
    pfi::lang::shared_ptr<framework::mixer::mixer> mixer,
    pfi::lang::shared_ptr<fv_converter::datum_to_fv_converter> converter)
    : mixer_(mixer),
      mixable_holder_(new framework::mixable_holder),
      converter_(converter) {
  clustering_.set_model(mixable_clustering::model_ptr(clustering_method));
  wm_.set_model(
      mixable_weight_manager::model_ptr(new fv_converter::weight_manager));

  mixer_->set_mixable_holder(mixable_holder_);
  mixable_holder_->register_mixable(&clustering_);
  mixable_holder_->register_mixable(&wm_);

  converter_->set_weight_manager(wm_.get_model());
}

clustering::~clustering() {
}

void clustering::push(const std::vector<datum>& points) {
  clustering_.get_model()->push(to_weighted_point_vector(points));
}

datum clustering::get_nearest_center(const datum& point) const {
  return to_datum(
      clustering_.get_model()->get_nearest_center(to_sfv_const(point)));
}

std::vector<std::pair<double, datum> > clustering::get_nearest_members(
    const datum& point) const {
  return to_weighted_datum_vector(
      clustering_.get_model()->get_nearest_members(to_sfv_const(point)));
}

std::vector<datum> clustering::get_k_center() const {
  return to_datum_vector(clustering_.get_model()->get_k_center());
}

std::vector<std::vector<std::pair<double, datum> > >
clustering::get_core_members() const {
  std::vector<std::vector<weighted_point> > src =
      clustering_.get_model()->get_core_members();

  std::vector<std::vector<std::pair<double, datum> > >  ret;
  ret.reserve(src.size());
  std::transform(
      src.begin(), src.end(), std::back_inserter(ret), pfi::lang::bind(
          &clustering::to_weighted_datum_vector, this, pfi::lang::_1));

  return ret;
}

size_t clustering::get_revision() const {
  return clustering_.get_model()->get_revision();
}

// private

sfv_t clustering::to_sfv(const datum& dat) {
  fv_converter::datum dat_internal;
  framework::convert<datum, fv_converter::datum>(dat, dat_internal);
  sfv_t ret;
  converter_->convert_and_update_weight(dat_internal, ret);
  sort_and_merge(ret);
  return ret;
}

sfv_t clustering::to_sfv_const(const datum& dat) const {
  fv_converter::datum dat_internal;
  framework::convert<datum, fv_converter::datum>(dat, dat_internal);
  sfv_t ret;
  converter_->convert(dat_internal, ret);
  sort_and_merge(ret);
  return ret;
}

datum clustering::to_datum(const sfv_t& src) const {
  fv_converter::datum ret_internal;
  datum ret;
  fv_converter::revert_feature(src, ret_internal);
  framework::convert<fv_converter::datum, datum>(ret_internal, ret);
  return ret;
}

weighted_point clustering::to_weighted_point(const datum& src) {
  weighted_point ret;
  ret.data = to_sfv(src);
  ret.weight = 1;
  ret.free_long = 1;
  ret.free_double = 1;
  ret.original = src;
  return ret;
}

std::pair<double, datum> clustering::to_weighted_datum(
    const weighted_point& src) const {
  return std::make_pair(src.weight, src.original);
}

std::vector<datum> clustering::to_datum_vector(
    const std::vector<sfv_t>& src) const {
  std::vector<datum> ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_datum, this, pfi::lang::_1));
  return ret;
}

std::vector<weighted_point> clustering::to_weighted_point_vector(
    const std::vector<datum>& src) {
  std::vector<weighted_point> ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_weighted_point, this, pfi::lang::_1));
  return ret;
}

std::vector<std::pair<double, datum> > clustering::to_weighted_datum_vector(
    const std::vector<weighted_point>& src) const {
  std::vector<std::pair<double, datum> > ret;
  ret.reserve(src.size());
  std::transform(src.begin(), src.end(), std::back_inserter(ret),
      pfi::lang::bind(&clustering::to_weighted_datum, this, pfi::lang::_1));
  return ret;
}

}  // namespace driver
}  // namespace jubatus
