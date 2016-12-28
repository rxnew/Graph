/**
 * @file footprints.hpp
 * @brief header of Footprints class
 */

#pragma once

#include <unordered_set>

namespace graph {
namespace util {
template <class T, class Hash>
class Footprints {
 private:
  std::unordered_set<T, Hash> footprints_;

 public:
  Footprints() = default;
  Footprints(const Footprints&) = default;
  Footprints(Footprints&&) noexcept = default;
  ~Footprints() = default;

  auto operator=(const Footprints&) -> Footprints& = default;
  auto operator=(Footprints&&) -> Footprints& = default;

  auto clear() -> void;
  auto leave(const T& x) -> void;
  auto exist(const T& x) const -> bool;
};
}
}

#include "footprints/footprints_impl.hpp"
