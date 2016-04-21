#pragma once

namespace dag {
template <class Vertex>
inline DirectedGraph<Vertex>::DirectedGraph(size_t size)
  : Super(size), next_(size), prev_(size) {
}

template <class Vertex>
inline DirectedGraph<Vertex>::DirectedGraph(const Vertices& vertices)
  : Super(vertices), next_(vertices.size()), prev_(vertices.size()) {
}

template <class Vertex>
inline DirectedGraph<Vertex>::DirectedGraph(Vertices&& vertices)
  : Super(std::move(vertices)),
    next_(this->vertices_.size()),
    prev_(this->vertices_.size()) {
}

template <class Vertex>
auto DirectedGraph<Vertex>::getSourceVertices() const -> Vertices {
  Vertices source_vertices;
  for(const auto& v : this->vertices_) {
    if(!this->getIndegree(v)) source_vertices.insert(v);
  }
  return std::move(source_vertices);
}

template <class Vertex>
auto DirectedGraph<Vertex>::getSinkVertices() const -> Vertices {
  Vertices sink_vertices;
  for(const auto& v : this->vertices_) {
    if(!this->getOutdegree(v)) sink_vertices.insert(v);
  }
  return std::move(sink_vertices);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::getNeighbors(const Vertex& v) const
  -> const Vertices& {
  return this->getNextVertices(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::getNextVertices(const Vertex& v) const
  -> const Vertices& {
  return Super::_getNeighbors(v, this->next_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::getPrevVertices(const Vertex& v) const
  -> const Vertices& {
  return Super::_getNeighbors(v, this->prev_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::getOutdegree(const Vertex& v) const
  -> size_t {
  return this->getNextVertices(v).size();
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::getIndegree(const Vertex& v) const
  -> size_t {
  return this->getPrevVertices(v).size();
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::addVertex(const Vertex& v) -> void {
  Super::addVertex(v);
  this->next_.emplace(v, Vertices());
  this->prev_.emplace(v, Vertices());
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::removeVertex(const Vertex& v) -> void {
  Super::removeVertex(v);
  Super::_removeVertexAdjacencyList(v, this->next_);
  Super::_removeVertexAdjacencyList(v, this->prev_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::addEdge(const Vertex& v,
                                           const Vertex& u) -> void {
  this->next_[v].insert(u);
  this->prev_[u].insert(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::removeEdge(const Vertex& v,
                                              const Vertex& u) -> void {
  this->next_[v].erase(u);
  this->prev_[u].erase(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::existEdge(const Vertex& v,
                                             const Vertex& u) const -> bool {
  return Super::_existEdge(v, u, this->next_);
}
}
