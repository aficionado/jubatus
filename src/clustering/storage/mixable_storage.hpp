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

#include "./storage.hpp"

namespace jubatus {
namespace clustering {

struct mixable_storage : public framework::mixable<
    jubatus::clustering::storage,
    jubatus::clustering::diff_t> {
 public:
  void clear() {}

  jubatus::clustering::diff_t get_diff_impl() const {
    return get_model()->get_diff();
  }

  void mix_impl(
      const jubatus::clustering::diff_t& lhs,
      const jubatus::clustering::diff_t& rhs,
      jubatus::clustering::diff_t& mixed) const {
    mixed = lhs;
    get_model()->reduce(rhs, mixed);
  }

  void put_diff_impl(const jubatus::clustering::diff_t& v) {
    get_model()->put_diff(v);
  }
};

}  // namespace clustering
}  // namespace jubatus
