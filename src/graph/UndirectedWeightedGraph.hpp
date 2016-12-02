/**
 * undirected unweighted graph
 */

#ifndef UNDIRECTED_WEIGHTED_GRAPH_
#define UNDIRECTED_WEIGHTED_GRAPH_

#include "WeightedGraph.hpp"

namespace vinalx {

namespace graph {

class UndirectedWeightedGraph : public WeightedGraph {
  public:
    UndirectedWeightedGraph(size_t vertex_num = 0)
        : WeightedGraph(vertex_num) {}

    void AddEdge(Vertex vertex1, Vertex vertex2, int weight) {
        WeightedGraph::AddEdge(vertex1, vertex2, weight);
        WeightedGraph::AddEdge(vertex2, vertex1, weight);
    }

    void RemoveEdge(Vertex vertex1, Vertex vertex2) {
        WeightedGraph::RemoveEdge(vertex1, vertex2);
        WeightedGraph::RemoveEdge(vertex2, vertex1);
    }
};

}  // namespace graph
}  // namespace vinalx

#endif  // UNDIRECTED_WEIGHTED_GRAPH_
