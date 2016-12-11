/**
 * shortest path for positive weighted graphs
 */
#ifndef GRAPH_SHORTEST_PATH_
#define GRAPH_SHORTEST_PATH_

#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include "graph/WeightedGraph.hpp"

namespace vinalx {

namespace graph {

namespace shortest_path {

namespace {

// helper function
template <typename Container>
inline bool Has(
    const Container& container, const typename Container::value_type& value) {
    return std::find(begin(container), end(container), value) != end(container);
}

}  // anonymous namespace

/**
 * dijkstra's algorithm
 * @param graph the weighted graph for calculation
 * @param from  starting vertex
 * @param to    destination vertex
 * @return      total weight of shortest path
 */
int Dijkstra(const Graph& graph, Graph::Vertex from, Graph::Vertex to) {
    std::vector<int> distance_to(graph.VertexSize(), INT_MAX);
    distance_to[from] = 0;
    std::set<std::pair<int, Graph::Vertex>> dijk_pq;
    dijk_pq.insert({0, from});
    for (; not dijk_pq.empty();) {
        auto shortest = *begin(dijk_pq);
        dijk_pq.erase(begin(dijk_pq));
        auto current_vertex = shortest.second;
        for (auto edge : graph.AdjacentEdges(current_vertex)) {
            auto new_distance = distance_to[current_vertex] + edge.weight;
            if (distance_to[edge.to] > new_distance) {
                dijk_pq.erase({distance_to[edge.to], edge.to});
                dijk_pq.insert({new_distance, edge.to});
                distance_to[edge.to] = new_distance;
            }
        }
    }
    return distance_to[to];
}

/**
 * shortest path faster algorithm
 * @param graph the weighted graph for calculation
 * @param from  starting vertex
 * @param to    destination vertex
 * @return      total weight of shortest path
 */
int Spfa(const Graph& graph, Graph::Vertex from, Graph::Vertex to) {
    std::vector<int> distance_to(graph.VertexSize(), INT_MAX);
    distance_to[from] = 0;
    std::deque<Graph::Vertex> bfs_queue;
    bfs_queue.push_back(from);

    for (; not bfs_queue.empty();) {
        auto current_vertex = bfs_queue.front();
        bfs_queue.pop_front();
        for (const auto& edge : graph.AdjacentEdges(current_vertex)) {
            auto new_distance = distance_to[current_vertex] + edge.weight;
            if (distance_to[edge.to] > new_distance) {
                distance_to[edge.to] = new_distance;
                if (not Has(bfs_queue, edge.to)) {
                    bfs_queue.push_back(edge.to);
                }
            }
        }
    }
    return distance_to[to];
}

/**
 * floyd;s algorithm
 * @param graph the weighted graph for calculation
 * @return      the matrix whose content is the shortest length between two
 * index
 */
std::vector<std::vector<int>> Floyd(const Graph& graph) {
    std::vector<std::vector<int>> distance(
        graph.VertexSize(), std::vector<int>(graph.VertexSize(), INT_MAX));
    for (Graph::Vertex v = 0; v < graph.VertexSize(); ++v) {
        for (const auto& edge : graph.AdjacentEdges(v)) {
            distance[v][edge.to] = edge.weight;
        }
    }
    for (Graph::Vertex k = 0; k < graph.VertexSize(); ++k) {
        for (Graph::Vertex i = 0; i < graph.VertexSize(); ++i) {
            for (Graph::Vertex j = 0; j < graph.VertexSize(); ++j) {
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    return distance;
}

}  // namespace shortest_path

}  // namespace graph

}  // namespace vinalx

#endif  // GRAPH_SHORTEST_PATH_
