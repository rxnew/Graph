#pragma once

namespace graph {
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
    next_(vertices_.size()),
    prev_(vertices_.size()) {
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_neighbors(const Vertex& v) const
  -> const Vertices& {
  return get_next_vertices(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::add_vertex(const Vertex& v) -> void {
  Super::add_vertex(v);
  next_.emplace(v, Vertices());
  prev_.emplace(v, Vertices());
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::remove_vertex(const Vertex& v) -> void {
  Super::remove_vertex(v);
  Super::_remove_vertex(v, next_);
  Super::_remove_vertex(v, prev_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::add_edge(const Vertex& v, const Vertex& u)
  -> void {
  next_[v].insert(u);
  prev_[u].insert(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::remove_edge(const Vertex& v, const Vertex& u)
  -> void {
  next_[v].erase(u);
  prev_[u].erase(v);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::exist_edge(const Vertex& v, const Vertex& u)
  const -> bool {
  return Super::_exist_edge(v, u, next_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_degree(const Vertex& v) const
  -> size_t {
  return get_indegree(v) + get_outdegree(v);
}

template <class Vertex>
auto DirectedGraph<Vertex>::collect_source_vertices() const -> Vertices {
  Vertices source_vertices;
  for(const auto& v : vertices_) {
    if(!get_indegree(v)) source_vertices.insert(v);
  }
  return std::move(source_vertices);
}

template <class Vertex>
auto DirectedGraph<Vertex>::collect_sink_vertices() const -> Vertices {
  Vertices sink_vertices;
  for(const auto& v : vertices_) {
    if(!get_outdegree(v)) sink_vertices.insert(v);
  }
  return std::move(sink_vertices);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::is_source_vertex(const Vertex& v) const
  -> bool {
  return get_prev_vertices(v).empty();
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::is_sink_vertex(const Vertex& v) const
  -> bool {
  return get_next_vertices(v).empty();
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_next_vertices(const Vertex& v) const
  -> const Vertices& {
  return Super::_get_neighbors(v, next_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_prev_vertices(const Vertex& v) const
  -> const Vertices& {
  return Super::_get_neighbors(v, prev_);
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_outdegree(const Vertex& v) const
  -> size_t {
  return get_next_vertices(v).size();
}

template <class Vertex>
inline auto DirectedGraph<Vertex>::get_indegree(const Vertex& v) const
  -> size_t {
  return get_prev_vertices(v).size();
}
}
