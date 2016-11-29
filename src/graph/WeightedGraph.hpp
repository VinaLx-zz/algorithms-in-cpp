/**
 * directed weighted graph
 */

#ifndef WEIGHTED_GRAPH_HPP_
#define WEIGHTED_GRAPH_HPP_

#include <cstddef>
#include <list>
#include <vector>

namespace vinalx {

class WeightedGraph {
  public:
    /**
     * for simplicity, use continuous unsigned integer as vertex
     */
    using Vertex = size_t;

    /**
     * edge used in all types of graph
     */
    struct Edge {
        Edge(Vertex from, Vertex to, int weight = 1)
            : from(from), to(to), weight(weight) {}
        Vertex from;
        Vertex to;
        int weight;
    };

    /**
     * initialize the graph with the number of vertices, default to 0
     * @param vertex_num initial amount of vertices of the graph
     */
    WeightedGraph(size_t vertex_num = 0)
        : adjacency_lists_(vertex_num), edge_num_(0) {}

    /**
     * add edge between two vertex
     * @param from the starting vertex of the edge
     * @param to the ending vertex of the edge
     * @param weight the weight of the edge
     */
    void AddEdge(Vertex from, Vertex to, int weight) {
        if (from >= VertexSize() or to >= VertexSize()) {
            return;
        }
        adjacency_lists_[from].push_back(Edge(from, to, weight));
        ++edge_num_;
    }

    /**
     * add a vertex, the number of vertex is always the currently largest vertex
     * number + 1
     * @return the vertex number add
     */
    Vertex AddVertex() {
        adjacency_lists_.emplace_back();
        return VertexSize() - 1;
    }

    /**
     * getter for vertices reachable in one step from the vertex specified
     * @param from the starting vertex
     * @return vertices adjacent to the starting vertex
     */
    std::vector<Vertex> AdjacentTo(Vertex from) const {
        std::vector<Vertex> vertices;
        for (const auto& edge : adjacency_lists_[from]) {
            vertices.push_back(edge.to);
        }
        return vertices;
    }

    /**
     * getter for the adjacent edges of a vertex
     * @param from the starting vertex of edges
     * @return edges starting from the vertex specified
     */
    std::vector<Edge> AdjacentEdges(Vertex from) const {
        std::vector<Edge> edges;
        for (const auto& edge : adjacency_lists_[from]) {
            edges.push_back(edge);
        }
        return edges;
    }

    void RemoveEdge(Vertex from, Vertex to) {
        adjacency_lists_[from].remove_if(
            [to](const Edge& edge) { return edge.to == to; });
    }

    /**
     * getter for the number of vertices
     */
    size_t VertexSize() const {
        return adjacency_lists_.size();
    }

    /**
     * getter for the number for edges
     */
    size_t EdgeSize() const {
        return edge_num_;
    }

  private:
    /**
     * adjacency lists of the graph
     */
    std::vector<std::list<Edge>> adjacency_lists_;

    /**
     * number of edges
     */
    size_t edge_num_;

};  // WeightedGraph

}  // namespace vinalx

#endif  // WEIGHTED_GRAPH_HPP_
