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
auto Graph<Vertex>::_getNeighbors(
    const Vertex& v, const AdjacencyList& list) -> const Vertices& {
  static const Vertices empty_vertices;
  auto pos = list.find(v);
  if(pos == list.cend()) return empty_vertices;
  return pos->second;
}

template <class Vertex>
auto Graph<Vertex>::_removeVertexAdjacencyList(
    const Vertex& v, AdjacencyList& list) -> void {
  for(const auto& u : list[v]) {
    list[u].erase(v);
  }
  list.erase(v);
}

template <class Vertex>
inline auto Graph<Vertex>::getVertices() const -> const Vertices& {
  return this->vertices_;
}

template <class Vertex>
inline auto Graph<Vertex>::getSize() const -> size_t {
  return this->vertices.size();
}

template <class Vertex>
inline auto Graph<Vertex>::addVertex(const Vertex& v) -> void {
  this->vertices_.insert(v);
}

template <class Vertex>
inline auto Graph<Vertex>::removeVertex(const Vertex& v) -> void {
  this->vertices_.erase(v);
}
}
