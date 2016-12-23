/**
 * @file bron_kerbosch_pivot.hpp
 * @brief header of BronKerboschPivot class
 */

#pragma once

#include <list>

namespace graph {
inline namespace algorithm {
template <class Graph>
class BronKerboschPivot {
 public:
  using Graph;
  using Vertex = Graph::Vertex;
  using Vertices = Graph::Vertices;
  using Cliques = std::list<Vertices>;

  BronKerboschPivot() = default;
  ~BronKerboschPivot() = default;

  auto solve(const Graph& g) & -> const Cliques&;
  auto solve(const Graph& g) && -> Cliques;

 private:
  auto _select_pivot(const Graph& g, const Vertices& p) -> Vertex;
  auto _report_maximal_clique(Vertices&& r) -> void;
  auto _solve(const Graph& g) -> void;
  auto _solve(const Graph& g, Vertices&& r, Vertices&& p, Vertices&& x) -> void;

  Cliques cliques;
};

template <class Graph>
auto bron_kerbosch_pivot(const Graph& g) -> BronKerboschPivot::Cliques;
}
}

#include "bron_kerbosch_pivot/bron_kerbosch_pivot_impl.hpp"
