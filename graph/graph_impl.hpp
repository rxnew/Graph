#pragma once

namespace graph {
template <class Vertex>
inline Graph<Vertex>::Graph(size_t size) : vertices_(size) {
}

template <class Vertex>
inline Graph<Vertex>::Graph(const Vertices& vertices) : vertices_(vertices) {
}

template <class Vertex>
inline Graph<Vertex>::Graph(Vertices&& vertices)
  : vertices_(std::move(vertices)) {
}

template <class Vertex>
inline auto Graph<Vertex>::get_vertices() const -> const Vertices& {
  return vertices_;
}

template <class Vertex>
inline auto Graph<Vertex>::get_size() const -> size_t {
  return vertices_.size();
}

template <class Vertex>
inline auto Graph<Vertex>::is_empty() const -> bool {
  return vertices_.empty();
}

template <class Vertex>
inline auto Graph<Vertex>::add_vertex(const Vertex& v) -> void {
  vertices_.insert(v);
}

template <class Vertex>
template <template <class...> class Container>
auto Graph<Vertex>::add_vertex(const Container<Vertex>& vertices) -> void {
  for(const auto& v : vertices) {
    add_vertex(v);
  }
}

template <class Vertex>
inline auto Graph<Vertex>::remove_vertex(const Vertex& v) -> void {
  vertices_.erase(v);
}

template <class Vertex>
template <template <class...> class Container>
auto Graph<Vertex>::remove_vertex(const Container<Vertex>& vertices) -> void {
  for(const auto& v : vertices) {
    remove_vertex(v);
  }
}

template <class Vertex>
inline auto Graph<Vertex>::is_isolated_vertex(const Vertex& v) const -> bool {
  return get_degree(v) == 0;
}

template <class Vertex>
auto Graph<Vertex>::_get_neighbors(const Vertex& v, const AdjacencyList& list)
  -> const Vertices& {
  static const Vertices empty_vertices;
  auto pos = list.find(v);
  if(pos == list.cend()) return empty_vertices;
  return pos->second;
}

template <class Vertex>
auto Graph<Vertex>::_remove_vertex(const Vertex& v, AdjacencyList& list) -> void {
  for(const auto& u : list[v]) {
    list[u].erase(v);
  }
  list.erase(v);
}

template <class Vertex>
auto Graph<Vertex>::_exist_edge(const Vertex& v, const Vertex& u,
                                const AdjacencyList& list) -> bool {
  auto pos = list.find(v);
  if(pos == list.cend()) return false;
  return pos->second.count(u);
}
}
