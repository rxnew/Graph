/**
 * @file set.hpp
 * @brief header of utilities of set
 */

#pragma once

#include <unordered_set>

namespace graph {
namespace util {
inline namespace set {
template <class T>
auto set_union(const std::unordered_set<T>& set, const T& value)
  -> std::unordered_set<T>;

template <class T>
auto set_union(const std::unordered_set<T>& lhs,
               const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_intersection(const std::unordered_set<T>& lhs,
                      const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;

template <class T>
auto set_difference(const std::unordered_set<T>& lhs,
                    const std::unordered_set<T>& rhs)
  -> std::unordered_set<T>;
}
}
}

#include "set/set_impl.hpp"
