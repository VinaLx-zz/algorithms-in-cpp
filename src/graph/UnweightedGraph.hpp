/**
 * unweighted directed graph
 */

#ifndef UNWEIGHTED_GRAPH_
#define UNWEIGHTED_GRAPH_

#include <vector>
#include "WeightedGraph.hpp"

namespace vinalx {

namespace graph {

class UnweightedGraph : public WeightedGraph {
  public:
    UnweightedGraph(size_t vertex_num = 0) : WeightedGraph(vertex_num) {}

    /**
     * add edge from a vertex to another
     */
    void AddEdge(Vertex from, Vertex to) {
        WeightedGraph::AddEdge(from, to, 1);
    }
};

}  // namespace graph
}  // namespace vianlx

#endif  // UNWEIGHTED_GRAPH_
