/**
 * @file undirected_graph.hpp
 * @brief header of UndirecteGraph class
 */

#pragma once

#include "graph.hpp"

namespace graph {
template <class Vertex>
class UndirectedGraph : public Graph<Vertex> {
 public:
  using Vertices = typename Graph<Vertex>::Vertices;
  using AdjacencyList = typename Graph<Vertex>::AdjacencyList;

 protected:
  AdjacencyList adjacency_list_;

 public:
  UndirectedGraph() = default;
  explicit UndirectedGraph(size_t size);
  explicit UndirectedGraph(const Vertices& vertices);
  explicit UndirectedGraph(Vertices&& vertices);
  UndirectedGraph(const UndirectedGraph&) = default;
  UndirectedGraph(UndirectedGraph&&) noexcept = default;
  virtual ~UndirectedGraph() = default;

  auto getNeighbors(const Vertex& v) const -> const Vertices&;
  auto getDegree(const Vertex& v) const -> size_t;
  auto addVertex(const Vertex& v) -> void;
  auto removeVertex(const Vertex& v) -> void;
  auto addEdge(const Vertex& v, const Vertex& u) -> void;
  auto removeEdge(const Vertex& v, const Vertex& u) -> void;
  auto existEdge(const Vertex& v, const Vertex& u) const -> bool;
};
}

#include "impl/undirected_graph_impl.hpp"
