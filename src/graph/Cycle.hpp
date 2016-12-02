#ifndef GRAPH_CYCLE_HPP_
#define GRAPH_CYCLE_HPP_

#include <algorithm>
#include <iostream>
#include "WeightedGraph.hpp"

namespace vinalx {

namespace graph {

namespace {

std::vector<Graph::Vertex> from;
std::vector<bool> marked;

Graph::Vertex Dfs(const Graph& graph, Graph::Vertex start) {
    for (auto vertex : graph.AdjacentTo(start)) {
        if (from[vertex] == -1) {
            from[vertex] = start;
            marked[vertex] = true;
            Graph::Vertex cycle_end = 0;
            if ((cycle_end = Dfs(graph, vertex)) != -1) {
                return cycle_end;
            }
        } else {
            from[vertex] = start;
            return start;
        }
    }
    return -1;
}

}  // anonymous namespace

// find one cycle for each connected component of a directed graph
std::vector<std::vector<Graph::Vertex>> FindCycle(const Graph& graph) {
    marked.assign(graph.VertexSize(), false);
    std::vector<std::vector<Graph::Vertex>> cycles;
    for (Graph::Vertex i = 0; i < graph.VertexSize(); ++i) {
        if (marked[i]) {
            continue;
        }
        from.assign(graph.VertexSize(), -1);
        from[i] = i;
        marked[i] = true;
        // dfs the whole connected component
        Graph::Vertex cycle_end = Dfs(graph, i);

        // didn't find a cycle
        if (cycle_end == -1) {
            continue;
        }
        std::vector<Graph::Vertex> cycle;
        auto current_vertex = cycle_end;

        // trace the path
        do {
            cycle.push_back(current_vertex);
            current_vertex = from[current_vertex];
        } while (current_vertex != cycle_end);
        std::reverse(cycle.begin(), cycle.end());
        cycles.push_back(cycle);
    }
    return cycles;
}

bool HasCycle(const Graph& graph) {
    return not FindCycle(graph).empty();
}

}  // namespace graph

}  // namespace vinalx

#endif  // GRAPH_CYCLE_HPP_
