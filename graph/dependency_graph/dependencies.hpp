#pragma once

namespace graph {
namespace dependencies {
template <class T>
struct Default {
  auto operator()(const T& lhs, const T& rhs) const -> bool;
};
}
}

#include "dependencies/dependencies_impl.hpp"
