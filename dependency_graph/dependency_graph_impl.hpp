#pragma once

namespace graph {
template <class Vertex, class Dependency, class Hash>
inline DependencyGraph<Vertex, Dependency, Hash>::
DependencyGraph(const Dependency& dependency, const Hash& hash)
  : dependency_(dependency), hash_(hash) {
}

template <class Vertex, class Dependency, class Hash>
inline DependencyGraph<Vertex, Dependency, Hash>::
DependencyGraph(size_t size, const Dependency& dependency, const Hash& hash)
  : Super(size), dependency_(dependency), hash_(hash) {
}

template <class Vertex, class Dependency, class Hash>
DependencyGraph<Vertex, Dependency, Hash>::
DependencyGraph(const Vertices& vertices,
                const Dependency& dependency, const Hash& hash)
  : Super(vertices.size()), dependency_(dependency), hash_(hash) {
  add_vertex(vertices);
}

template <class Vertex, class Dependency, class Hash>
auto DependencyGraph<Vertex, Dependency, Hash>::
add_vertex(const Vertex& v) -> void {
  Super::add_vertex(v);
  footprints_.clear();
  if(sources_.empty()) {
    sources_.insert(v);
    return;
  }
  for(const auto& source : sources_) {
    _add_vertex(v, source);
  }
  if(is_source_vertex(v)) sources_.insert(v);
}

template <class Vertex, class Dependency, class Hash>
auto DependencyGraph<Vertex, Dependency, Hash>::
remove_vertex(const Vertex& v) -> void {
  auto update_source_flag = is_source_vertex(v);
  const auto& next_vertices = get_next_vertices(v);
  Super::remove_vertex(v);
  if(!update_source_flag) return;
  for(const auto& u : next_vertices) {
    if(is_source_vertex(u)) sources_.insert(u);
  }
}

template <class Vertex, class Dependency, class Hash>
auto DependencyGraph<Vertex, Dependency, Hash>::
count_dependent_vertices(const Vertex& v) const -> int {
  footprints_.clear();
  return _count_dependent_vertices(get_next_vertices(v));
}

template <class Vertex, class Dependency, class Hash>
template <template <class...> class Container>
auto DependencyGraph<Vertex, Dependency, Hash>::
count_dependent_vertices(const Container<Vertex>& vertices) const -> int {
  footprints_.clear();
  return _count_dependent_vertices(vertices);
}

template <class Vertex, class Dependency, class Hash>
inline auto DependencyGraph<Vertex, Dependency, Hash>::
add_edge(const Vertex& v, const Vertex& u) -> void {
  Super::add_edge(v, u);
}

template <class Vertex, class Dependency, class Hash>
inline auto DependencyGraph<Vertex, Dependency, Hash>::
remove_edge(const Vertex& v, const Vertex& u) -> void {
  Super::remove_edge(v, u);
}

template <class Vertex, class Dependency, class Hash>
auto DependencyGraph<Vertex, Dependency, Hash>::
_add_vertex(const Vertex& v, const Vertex& pos) -> bool {
  if(footprints_.exist(pos)) return false;
  footprints_.leave(pos);
  auto add_flag = false;
  for(const auto& next : get_next_vertices(pos)) {
    add_flag |= _add_vertex(v, next);
  }
  if(add_flag) return true;
  if(!dependency_(pos, v)) return false;
  Super::add_edge(pos, v);
  return true;
}

template <class Vertex, class Dependency, class Hash>
template <template <class...> class Container>
auto DependencyGraph<Vertex, Dependency, Hash>::
_count_dependent_vertices(const Container<Vertex>& vertices) const -> int {
  auto count = 0;
  for(const auto& v : vertices) {
    if(footprints_.exist(v)) continue;
    footprints_.leave(v);
    const auto& next = get_next_vertices(v);
    count += _count_dependent_vertices(next) + next.size();
  }
  return count;
}
}
