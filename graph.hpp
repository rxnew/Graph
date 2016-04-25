/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

#include <unordered_set>
#include <unordered_map>

namespace graph {
template <class Vertex>
class Graph {
 public:
  using Vertices = std::unordered_set<Vertex>;
  using AdjacencyList = std::unordered_map<Vertex, Vertices>;

 protected:
  Vertices vertices_;

  static auto _getNeighbors(const Vertex& v,
                            const AdjacencyList& list) -> const Vertices&;
  static auto _removeVertexAdjacencyList(const Vertex& v,
                                         AdjacencyList& list) -> void;
  static auto _existEdge(const Vertex& v, const Vertex& u,
                         const AdjacencyList& list) -> bool;

 public:
  Graph() = default;
  explicit Graph(size_t size);
  explicit Graph(const Vertices& vertices);
  explicit Graph(Vertices&& vertices);
  Graph(const Graph&) = default;
  Graph(Graph&&) noexcept = default;
  virtual ~Graph() = default;

  auto operator=(const Graph&) -> Graph& = default;
  auto operator=(Graph&&) -> Graph& = default;

  auto getVertices() const -> const Vertices&;
  auto getSize() const -> size_t;
  virtual auto getNeighbors(const Vertex& v) const -> const Vertices& = 0;
  virtual auto addVertex(const Vertex& v) -> void;
  virtual auto removeVertex(const Vertex& v) -> void;
  virtual auto addEdge(const Vertex& v, const Vertex& u) -> void = 0;
  virtual auto removeEdge(const Vertex& v, const Vertex& u) -> void = 0;
  virtual auto existEdge(const Vertex& v, const Vertex& u) const -> bool = 0;
};
}

#include "impl/graph_impl.hpp"
