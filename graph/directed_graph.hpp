/**
 * @file directed_graph.hpp
 * @brief header of DirectedGraph class
 */

#pragma once

#include "graph.hpp"

namespace graph {
template <class V>
class DirectedGraph : public Graph<V> {
 protected:
  using Super = Graph<V>;

 public:
  using Vertex = V;
  using Vertices = typename Super::Vertices;
  using AdjacencyList = typename Super::AdjacencyList;

  DirectedGraph() = default;
  explicit DirectedGraph(size_t size);
  explicit DirectedGraph(const Vertices& vertices);
  explicit DirectedGraph(Vertices&& vertices);
  DirectedGraph(const DirectedGraph&) = default;
  DirectedGraph(DirectedGraph&&) noexcept = default;
  virtual ~DirectedGraph() = default;

  auto operator=(const DirectedGraph&) -> DirectedGraph& = default;
  auto operator=(DirectedGraph&&) noexcept -> DirectedGraph& = default;

  virtual auto get_neighbors(const Vertex& v) const -> const Vertices& final;
  virtual auto add_vertex(const Vertex& v) -> void override;
  virtual auto remove_vertex(const Vertex& v) -> void override;
  virtual auto add_edge(const Vertex& v, const Vertex& u) -> void override;
  virtual auto remove_edge(const Vertex& v, const Vertex& u) -> void override;
  virtual auto exist_edge(const Vertex& v, const Vertex& u) const
    -> bool override;
  virtual auto get_degree(const Vertex& v) const -> size_t override;
  virtual auto collect_source_vertices() const -> Vertices;
  virtual auto collect_sink_vertices() const -> Vertices;
  auto is_source_vertex(const Vertex& v) const -> bool;
  auto is_sink_vertex(const Vertex& v) const -> bool;
  auto get_next_vertices(const Vertex& v) const -> const Vertices&;
  auto get_prev_vertices(const Vertex& v) const -> const Vertices&;
  auto get_outdegree(const Vertex& v) const -> size_t;
  auto get_indegree(const Vertex& v) const -> size_t;

 protected:
  AdjacencyList next_;
  AdjacencyList prev_;
};
}

#include "directed_graph/directed_graph_impl.hpp"
