namespace dep {
template <class T, class Hash>
inline auto Footprints<T, Hash>::clear() -> void {
  this->footprints_.clear();
}

template <class T, class Hash>
inline auto Footprints<T, Hash>::leave(const T& x) -> void {
  this->footprints_.insert(x);
}

template <class T, class Hash>
inline auto Footprints<T, Hash>::exist(const T& x) const -> bool {
  return this->footprints_.cend() != this->footprints_.find(x);
}
}
