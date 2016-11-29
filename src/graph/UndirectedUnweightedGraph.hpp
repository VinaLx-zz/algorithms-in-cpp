/**
 * undirected unweighted graph
 */

#ifndef UNDIRECTED_UNWEIGHTED_GRAPH_HPP_
#define UNDIRECTED_UNWEIGHTED_GRAPH_HPP_

#include "UnweightedGraph.hpp"

namespace vinalx {

class UndirectedUnweightedGraph : public UnweightedGraph {
  public:
    UndirectedUnweightedGraph(size_t vertex_num)
        : UnweightedGraph(vertex_num) {}

    void AddEdge(Vertex vertex1, Vertex vertex2) {
        UnweightedGraph::AddEdge(vertex1, vertex2);
        UnweightedGraph::AddEdge(vertex2, vertex1);
    }

    void RemoveEdge(Vertex vertex1, Vertex vertex2) {
        UnweightedGraph::RemoveEdge(vertex1, vertex2);
        UnweightedGraph::RemoveEdge(vertex2, vertex1);
    }
};

}  // namespace vinalx

#endif  // UNDIRECTED_UNWEIGHTED_GRAPH_HPP_
