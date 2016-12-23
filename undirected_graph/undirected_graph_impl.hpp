#pragma once

namespace graph {
template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(size_t size)
  : Super(size), adjacency_list_(size) {
}

template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(const Vertices& vertices)
  : Super(vertices), adjacency_list_(vertices.size()) {
}

template <class Vertex>
inline UndirectedGraph<Vertex>::UndirectedGraph(Vertices&& vertices)
  : Super(std::move(vertices)), adjacency_list_(this->vertices_.size()) {
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::get_neighbors(const Vertex& v) const
  -> const Vertices& {
  return Super::_get_neighbors(v, adjacency_list_);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::add_vertex(const Vertex& v) -> void {
  Super::add_vertex(v);
  adjacency_list_.emplace(v, Vertices());
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::remove_vertex(const Vertex& v) -> void {
  Super::remove_vertex(v);
  Super::_remove_vertex(v, adjacency_list_);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::add_edge(const Vertex& v, const Vertex& u)
  -> void {
  adjacency_list_[v].insert(u);
  adjacency_list_[u].insert(v);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::remove_edge(const Vertex& v,
                                                 const Vertex& u) -> void {
  adjacency_list_[v].erase(u);
  adjacency_list_[u].erase(v);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::exist_edge(const Vertex& v,
                                                const Vertex& u) const -> bool {
  return Super::_exist_edge(v, u, adjacency_list_);
}

template <class Vertex>
inline auto UndirectedGraph<Vertex>::get_degree(const Vertex& v) const
  -> size_t {
  return get_neighbors(v).size();
}
}
