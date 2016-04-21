#pragma once

namespace graph {
template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(size_t size)
  : Graph<Vertex>(size), adjacency_list_(size) {
}

template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(const Vertices& vertices)
  : Graph<Vertex>(vertices), adjacency_list_(vertices.size()) {
  this->_initAdjacencyList();
}

template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(Vertices&& vertices)
  : Graph<Vertex>(std::move(vertices)),
    adjacency_list_(this->vertices_.size()) {
  this->_initAdjacencyList();
}

template <class Vertex>
auto UndirectedGraph<Vertex>::_initAdjacencyList() -> void {
  for(const auto& v : this->vertices_) {
    this->adjacency_list_.emplace(v, Vertices());
  }
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::getNeighbors(const Vertex& v) const
  -> const Vertices& {
  return Graph<Vertex>::_getNeighbors(v, this->adjacency_list_);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::getDegree(const Vertex& v) const
  -> size_t {
  return this->getNeighbors(v).size();
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::addVertex(const Vertex& v) -> void {
  Graph<Vertex>::addVertex(v);
  this->adjacency_list_.emplace(v, Vertices());
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::removeVertex(const Vertex& v) -> void {
  Graph<Vertex>::removeVertex(v);
  Graph<Vertex>::_removeVertexAdjacencyList(v, this->adjacency_list_);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::addEdge(const Vertex& v,
                                             const Vertex& u) -> void {
  this->adjacency_list_[v].insert(u);
  this->adjacency_list_[u].insert(v);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::removeEdge(const Vertex& v,
                                                const Vertex& u) -> void {
  this->adjacency_list_[v].erase(u);
  this->adjacency_list_[u].erase(v);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::existEdge(const Vertex& v,
                                               const Vertex& u) const -> bool {
  return this->adjacency_list_[v].count(u);
}
}
