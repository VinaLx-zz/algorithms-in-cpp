/**
 * unweighted directed graph
 */

#ifndef UNWEIGHTED_GRAPH_
#define UNWEIGHTED_GRAPH_

#include <vector>
#include "WeightedGraph.hpp"

namespace vinalx {

class UnweightedGraph : public WeightedGraph {
  public:
    UnweightedGraph(size_t vertex_num = 0) : WeightedGraph(0) {}

    /**
     * add edge from a vertex to another
     */
    void AddEdge(Vertex from, Vertex to) {
        WeightedGraph::AddEdge(from, to, 1);
    }

};  // namespace vianlx

#endif  // UNWEIGHTED_GRAPH_
