#ifndef GRAPH_TOPOLOGICAL_SORT_
#define GRAPH_TOPOLOGICAL_SORT_

#include <vector>
#include <algorithm>
#include "Cycle.hpp"
#include "WeightedGraph.hpp"

namespace vinalx {

namespace graph {

namespace {

std::vector<bool> mark;

void Dfs(const Graph& graph, Graph::Vertex start, std::vector<Graph::Vertex>& result) {
    for (auto vertex : graph.AdjacentTo(start)) {
        if (not mark[vertex]) {
            Dfs(graph, vertex, result);
            result.push_back(vertex);
        }
    }
}

}  // anonymous namespace

std::vector<Graph::Vertex> TopologicalSort(const Graph& graph) {
    if (HasCycle(graph)) {
        return {};
    }
    mark.assign(graph.VertexSize(), false);
    std::vector<Graph::Vertex> result;
    for (Graph::Vertex v = 0; v < graph.VertexSize(); ++v) {
        if (not mark[v]) {
            Dfs(graph, v, result);
            result.push_back(v);
        }
    }
    std::reverse(begin(result), end(result));
    return result;
}

}  // namespace graph

}  // namespace vinalx

#endif  // GRAPH_TOPOLOGICAL_SORT_
