/**
 * @file graph.hpp
 * @brief header of Graph class
 */

#pragma once

#include <unordered_set>
#include <unordered_map>

namespace graph {
template <class V>
class Graph {
 public:
  using Vertex = V;
  using Vertices = std::unordered_set<Vertex>;
  using AdjacencyList = std::unordered_map<Vertex, Vertices>;

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

  auto get_vertices() const -> const Vertices&;
  auto get_size() const -> size_t;
  auto is_empty() const -> bool;
  virtual auto get_neighbors(const Vertex& v) const -> const Vertices& = 0;
  virtual auto add_vertex(const Vertex& v) -> void;
  template <template <class...> class Container>
  auto add_vertices(const Container<Vertex>& vertices) -> void;
  virtual auto remove_vertex(const Vertex& v) -> void;
  template <template <class...> class Container>
  auto remove_vertices(const Container<Vertex>& vertices) -> void;
  virtual auto add_edge(const Vertex& v, const Vertex& u) -> void = 0;
  virtual auto remove_edge(const Vertex& v, const Vertex& u) -> void = 0;
  virtual auto exist_edge(const Vertex& v, const Vertex& u) const -> bool = 0;
  virtual auto get_degree(const Vertex& v) const -> size_t = 0;
  virtual auto is_isolated_vertex(const Vertex& v) const -> bool;

 protected:
  Vertices vertices_;

  static auto _get_neighbors(const Vertex& v, const AdjacencyList& list)
    -> const Vertices&;
  static auto _remove_vertex(const Vertex& v, AdjacencyList& list) -> void;
  static auto _exist_edge(const Vertex& v, const Vertex& u,
                          const AdjacencyList& list) -> bool;
};
}

#include "graph/graph_impl.hpp"
