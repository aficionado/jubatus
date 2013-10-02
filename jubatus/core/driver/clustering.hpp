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

#ifndef JUBATUS_DRIVER_CLUSTERING_HPP_
#define JUBATUS_DRIVER_CLUSTERING_HPP_

#include <utility>
#include <vector>
#include <pficommon/lang/shared_ptr.h>
#include "../clustering/types.hpp"
#include "../clustering/clustering.hpp"
#include "../framework/mixable.hpp"
#include "../../server/framework/mixer/mixer.hpp"
#include "../fv_converter/datum.hpp"
#include "../fv_converter/datum_to_fv_converter.hpp"
#include "../fv_converter/mixable_weight_manager.hpp"

namespace jubatus {
namespace core {
namespace driver {

class mixable_clustering : public core::framework::mixable<
    clustering::clustering,
    clustering::diff_t> {
 public:
  void clear() {}

  clustering::diff_t get_diff_impl() const {
    return get_model()->get_diff();
  }

  void mix_impl(
      const clustering::diff_t& lhs,
      const clustering::diff_t& rhs,
      clustering::diff_t& mixed) const {
    mixed = lhs;
    get_model()->reduce(rhs, mixed);
  }

  void put_diff_impl(const clustering::diff_t& v) {
    get_model()->put_diff(v);
  }
};

class clustering {
 public:
  clustering(
      core::clustering::clustering* clustering_method,
      pfi::lang::shared_ptr<server::framework::mixer::mixer> mixer,
      pfi::lang::shared_ptr<fv_converter::datum_to_fv_converter> converter);
  virtual ~clustering();

  server::framework::mixer::mixer* get_mixer() const {
    return mixer_.get();
  }

  pfi::lang::shared_ptr<framework::mixable_holder> get_mixable_holder() const {
    return mixable_holder_;
  }

  void push(const std::vector<fv_converter::datum>& points);

  fv_converter::datum get_nearest_center(const datum& point) const;
  std::vector<std::pair<double, datum> >  get_nearest_members(
    const fv_converter::datum& point) const;

  std::vector<datum> get_k_center() const;
  std::vector<std::vector<std::pair<double, datum> > > get_core_members() const;

  size_t get_revision() const;

  // TODO(beam2d): Implement clear().

 private:
  common::sfv_t to_sfv(const datum& dat);
  common::sfv_t to_sfv_const(const datum& dat) const;
  datum to_datum(const common::sfv_t& src) const;
  core::clustering::weighted_point to_weighted_point(const fv_converter::datum& src);
  std::pair<double, datum>
  to_weighted_datum(const core::clustering::weighted_point& src) const;
  std::vector<datum> to_datum_vector(const std::vector<common::sfv_t>& src) const;
  std::vector<core::clustering::weighted_point> to_weighted_point_vector(
      const std::vector<datum>& src);
  std::vector<std::pair<double, datum> > to_weighted_datum_vector(
      const std::vector<core::clustering::weighted_point>& src) const;

  pfi::lang::shared_ptr<server::framework::mixer::mixer> mixer_;
  pfi::lang::shared_ptr<framework::mixable_holder> mixable_holder_;

  pfi::lang::shared_ptr<fv_converter::datum_to_fv_converter> converter_;
  pfi::lang::shared_ptr<mixable_clustering> clustering_;
  pfi::lang::shared_ptr<fv_converter::mixable_weight_manager> wm_;
};

}  // namespace driver
}  // namespace core
}  // namespace jubatus

#endif  // JUBATUS_DRIVER_CLUSTERING_HPP_
