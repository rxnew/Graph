/**
 * @file undirected_graph.hpp
 * @brief header of UndirecteGraph class
 */

#pragma once

#include "graph.hpp"

namespace graph {
template <class Vertex>
class UndirectedGraph : public Graph<Vertex> {
 protected:
  using Super = Graph<Vertex>;

 public:
  using Vertices = typename Super::Vertices;
  using AdjacencyList = typename Super::AdjacencyList;

  UndirectedGraph() = default;
  explicit UndirectedGraph(size_t size);
  explicit UndirectedGraph(const Vertices& vertices);
  explicit UndirectedGraph(Vertices&& vertices);
  UndirectedGraph(const UndirectedGraph&) = default;
  UndirectedGraph(UndirectedGraph&&) noexcept = default;
  virtual ~UndirectedGraph() = default;

  auto operator=(const UndirectedGraph&) -> UndirectedGraph& = default;
  auto operator=(UndirectedGraph&&) -> UndirectedGraph& = default;

  virtual auto get_neighbors(const Vertex& v) const -> const Vertices& final;
  virtual auto add_vertex(const Vertex& v) -> void override;
  virtual auto remove_vertex(const Vertex& v) -> void override;
  virtual auto add_edge(const Vertex& v, const Vertex& u) -> void override;
  virtual auto remove_edge(const Vertex& v, const Vertex& u) -> void override;
  virtual auto exist_edge(const Vertex& v, const Vertex& u) const
    -> bool override;
  virtual auto get_degree(const Vertex& v) const -> size_t override;

 protected:
  AdjacencyList adjacency_list_;
};
}

#include "undirected_graph/undirected_graph_impl.hpp"
