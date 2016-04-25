/**
 * @file directed_graph.hpp
 * @brief header of DirectedGraph class
 */

#pragma once

#include "graph.hpp"

namespace graph {
template <class Vertex>
class DirectedGraph : public Graph<Vertex> {
 protected:
  using Super = Graph<Vertex>;

 public:
  using Vertices = typename Super::Vertices;
  using AdjacencyList = typename Super::AdjacencyList;

 protected:
  AdjacencyList next_;
  AdjacencyList prev_;

 public:
  DirectedGraph() = default;
  explicit DirectedGraph(size_t size);
  explicit DirectedGraph(const Vertices& vertices);
  explicit DirectedGraph(Vertices&& vertices);
  DirectedGraph(const DirectedGraph&) = default;
  DirectedGraph(DirectedGraph&&) noexcept = default;
  virtual ~DirectedGraph() = default;

  auto operator=(const DirectedGraph&) -> DirectedGraph& = default;
  auto operator=(DirectedGraph&&) -> DirectedGraph& = default;

  auto getSourceVertices() const -> Vertices;
  auto getSinkVertices() const -> Vertices;
  auto getNeighbors(const Vertex& v) const -> const Vertices&;
  auto getNextVertices(const Vertex& v) const -> const Vertices&;
  auto getPrevVertices(const Vertex& v) const -> const Vertices&;
  auto getOutdegree(const Vertex& v) const -> size_t;
  auto getIndegree(const Vertex& v) const -> size_t;
  auto addVertex(const Vertex& v) -> void;
  auto removeVertex(const Vertex& v) -> void;
  auto addEdge(const Vertex& v, const Vertex& u) -> void;
  auto removeEdge(const Vertex& v, const Vertex& u) -> void;
  auto existEdge(const Vertex& v, const Vertex& u) const -> bool;
};
}

#include "impl/directed_graph_impl.hpp"
