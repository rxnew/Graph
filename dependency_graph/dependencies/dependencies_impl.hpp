#pragma once

namespace graph {
namespace dependencies {
template <class T>
auto Default<T>::operator()(const T& lhs, const T& rhs) const -> bool {
  return lhs == rhs;
}
}
}
