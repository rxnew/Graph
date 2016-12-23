#pragma once

#include <cassert>

#include "../../util/set.hpp"

namespace graph {
inline namespace algorithm {
template <class Graph>
auto BronKerboschPivot<Graph>::solve(const Graph& g) & -> const Cliques& {
  _solve(g);
  return cliques;
}

template <class Graph>
auto BronKerboschPivot<Graph>::solve(const Graph& g) && -> Cliques {
  _solve(g);
  return std::move(cliques);
}

template <class Graph>
auto BronKerboschPivot<Graph>::_select_pivot(const Graph& g, const Vertices& p)
  -> Vertex {
  assert(!p.empty());

  auto pivot = *p.begin();
  auto max_neighbor_number = 0;
  for(const auto& v : p) {
    auto neighbor_number = g.get_degree(v);
    if(neighbor_number > max_neighbor_number) {
      max_neighbor_number = neighbor_number;
      pivot = v;
    }
  }
  return pivot;
}

template <class Graph>
inline auto BronKerboschPivot<Graph>::_report_maximal_clique(Vertices&& r)
  -> void {
  cliques.push_back(std::move(r));
}

template <class Graph>
auto BronKerboschPivot<Graph>::_solve(const Graph& g) -> void {
  cliques.clear();
  auto r = Vertices();
  auto p = g.get_vertices();
  auto x = Vertices();
  _solve(g, std::move(r), std::move(p), std::move(x));
}

template <class Graph>
auto BronKerboschPivot<Graph>::
_solve(const Graph& g, Vertices&& r, Vertices&& p, Vertices&& x) -> void {
  if(p.empty()) {
    if(x.empty()) _report_maximal_clique(std::move(r));
    return;
  }
  auto u = g.get_neighbors(_select_pivot(g, p));
  for(const auto& v : util::set_difference(p, u)) {
    auto nv = g.get_neighbors(v);
    _solve(g,
           util::set_union(r, v),
           util::set_intersection(p, nv),
           util::set_intersection(x, nv));
    p.erase(v);
    x.insert(v);
  }
}

template <class Graph>
inline auto bron_kerbosch_pivot(const Graph& g) -> BronKerboschPivot::Cliques {
  return BronKerboschPivot<Graph>().solve(g);
}
}
}
