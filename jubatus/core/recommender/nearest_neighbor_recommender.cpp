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

#include "nearest_neighbor_recommender.hpp"

#include <string>
#include <utility>
#include <vector>
#include <pficommon/data/serialization.h>
#include "../common/exception.hpp"

namespace jubatus {
namespace core {
namespace recommender {

nearest_neighbor_recommender::nearest_neighbor_recommender(
    pfi::lang::shared_ptr<nearest_neighbor::nearest_neighbor_base>
    nearest_neighbor_engine)
    : nearest_neighbor_engine_(nearest_neighbor_engine) {
}

void nearest_neighbor_recommender::similar_row(
    const common::sfv_t& query,
    std::vector<std::pair<std::string, float> >& ids,
    size_t ret_num) const {
  nearest_neighbor_engine_->similar_row(query, ids, ret_num);
}

void nearest_neighbor_recommender::neighbor_row(
    const common::sfv_t& query,
    std::vector<std::pair<std::string, float> >& ids,
    size_t ret_num) const {
  nearest_neighbor_engine_->neighbor_row(query, ids, ret_num);
}

void nearest_neighbor_recommender::clear() {
  orig_.clear();
  nearest_neighbor_engine_->clear();
}

void nearest_neighbor_recommender::clear_row(const std::string& id) {
  throw JUBATUS_EXCEPTION(common::unsupported_method(__func__));
}

void nearest_neighbor_recommender::update_row(
    const std::string& id,
    const common::sfv_t& diff) {
  orig_.set_row(id, diff);
  common::sfv_t row;
  orig_.get_row(id, row);
  nearest_neighbor_engine_->set_row(id, row);
}

void nearest_neighbor_recommender::get_all_row_ids(
    std::vector<std::string>& ids) const {
  nearest_neighbor_engine_->get_all_row_ids(ids);
}

std::string nearest_neighbor_recommender::type() const {
  return "nearest_neighbor_recommender:" + nearest_neighbor_engine_->type();
}

void nearest_neighbor_recommender::register_mixables_to_holder(
    framework::mixable_holder& holder) const {
  nearest_neighbor_engine_->register_mixables_to_holder(holder);
}

void nearest_neighbor_recommender::pack_impl(
    msgpack::packer<msgpack::sbuffer>& packer) const {
  nearest_neighbor_engine_->pack(packer);
}

void nearest_neighbor_recommender::unpack_impl(msgpack::object o) {
  nearest_neighbor_engine_->unpack(o);
}

}  // namespace recommender
}  // namespace core
}  // namespace jubatus
