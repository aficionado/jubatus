// Jubatus: Online machine learning framework for distributed environment
// Copyright (C) 2011 Preferred Infrastructure and Nippon Telegraph and Telephone Corporation.
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

#include <gtest/gtest.h>
#include "exception.hpp"
#include "key_matcher_factory.hpp"
#include "key_matcher.hpp"

namespace jubatus {
namespace core {
namespace fv_converter {

TEST(fv_converter, key_matcher_factory) {
  typedef pfi::lang::shared_ptr<key_matcher> m_t;

  key_matcher_factory f;
  ASSERT_TRUE(m_t(f.create_matcher("*"))->match("hogehgeo"));
  ASSERT_TRUE(m_t(f.create_matcher(""))->match("hogehgeo"));
  ASSERT_TRUE(
      m_t(f.create_matcher("*hogehoge"))->match("adslfjaldsfjadshogehoge"));
  ASSERT_FALSE(m_t(f.create_matcher("*hogehoge"))->match("hogehogea;lsdufi"));
  ASSERT_FALSE(
      m_t(f.create_matcher("hogehoge*"))->match("adslfjaldsfjadshogehoge"));
  ASSERT_TRUE(m_t(f.create_matcher("hogehoge*"))->match("hogehogea;lsdufi"));
  ASSERT_FALSE(m_t(f.create_matcher("hogehoge"))->match("hogefuga"));
  ASSERT_TRUE(m_t(f.create_matcher("hogehoge"))->match("hogehoge"));

  ASSERT_TRUE(m_t(f.create_matcher("/.*/hoge/"))->match("fuga/hoge"));
}

}  // namespace fv_converter
}  // namespace core
}  // namespace jubatus
