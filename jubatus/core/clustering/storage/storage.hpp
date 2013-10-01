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

#ifndef JUBATUS_CLUSTERING_STORAGE_STORAGE_HPP_
#define JUBATUS_CLUSTERING_STORAGE_STORAGE_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "../clustering_config.hpp"
#include "../types.hpp"
#include "event_dispatcher.hpp"

namespace jubatus {
namespace core {
namespace clustering {

enum storage_event_type {
  REVISION_CHANGE,
  UPDATE
};

class storage_serializer;

class storage : public event_dispatcher<storage_event_type, wplist> {
 public:
  storage(const std::string& name, const clustering_config& config);

  diff_t get_diff() const;
  void put_diff(const diff_t& d);
  void reduce(const diff_t&, diff_t& ret);

  size_t get_revision();

  virtual void add(const weighted_point& point) = 0;
  virtual wplist get_mine() const = 0;

  virtual wplist get_all() const;
  virtual wplist get_common() const;

  virtual bool save(std::ostream& ofs);
  virtual bool load(std::istream& ofs);

 protected:
  void increment_revision();

  size_t revision_;
  std::string name_;
  clustering_config config_;

  std::vector<std::pair<std::string, wplist> > common_;

 private:
  friend class storage_serializer;
  template <class Archive>
  void serialize(Archive &ar) {}
};


}  // namespace clustering
}  // namespace core
}  // namespace jubatus

#endif  // JUBATUS_CLUSTERING_STORAGE_STORAGE_HPP_
