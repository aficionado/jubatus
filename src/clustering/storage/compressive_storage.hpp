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

#ifndef JUBATUS_CLUSTERING_STORAGE_COMPRESSIVE_STORAGE_HPP_
#define JUBATUS_CLUSTERING_STORAGE_COMPRESSIVE_STORAGE_HPP_

#include <string>
#include <vector>
#include "storage.hpp"
#include "compressor/compressor.hpp"

namespace jubatus {
namespace clustering {

class storage_serializer;

class compressive_storage : public storage {
 public:
  compressive_storage(
      const std::string& name, const clustering_config& config);

  void add(const weighted_point& point);
  wplist get_mine() const;
  void set_compressor(
      pfi::lang::shared_ptr<compressor::compressor> compressor);

 private:
  void carry_up(size_t r);
  bool is_next_backet_full(size_t backet_number);
  bool reach_forgetting_threshold(size_t backet_number);
  void forget_weight(wplist& points);

  std::vector<wplist> mine_;
  size_t status_;
  pfi::lang::shared_ptr<compressor::compressor> compressor_;

  friend class storage_serializer;
  template <class Ar>
  void serialize(Ar &ar) {
    ar & status_ & mine_;
  }
};

}  // namespace clustering
}  // namespace jubatus

#endif  // JUBATUS_CLUSTERING_STORAGE_COMPRESSIVE_STORAGE_HPP_
