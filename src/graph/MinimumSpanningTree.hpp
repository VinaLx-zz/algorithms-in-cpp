#ifndef GRAPH_MINIMUM_SPANNING_TREE_
#define GRAPH_MINIMUM_SPANNING_TREE_

#include <functional>
#include <queue>
#include <vector>
#include "graph/UndirectedWeightedGraph.hpp"
#include "heap/Heap.hpp"
#include "union-find/UnionFind.hpp"

namespace vinalx {

namespace graph {

namespace mst {

struct Edge {
    Edge(Graph::Vertex v1, Graph::Vertex v2, int weight)
        : v1(v1), v2(v2), weight(weight) {}
    Graph::Vertex v1;
    Graph::Vertex v2;
    int weight;
};

namespace {

bool EdgeComp(const Edge& lhs, const Edge& rhs) {
    return lhs.weight > rhs.weight;
}

std::vector<Edge> ExtractEdge(const UndirectedWeightedGraph& graph) {
    std::vector<Edge> result;
    for (Graph::Vertex i = 0; i < graph.VertexSize(); ++i) {
        for (const auto& edge : graph.AdjacentEdges(i)) {
            if (edge.to > i) {
                result.emplace_back(i, edge.to, edge.weight);
            }
        }
    }
    return result;
}

void AddVertex(
    const UndirectedWeightedGraph& graph, Graph::Vertex vertex,
    std::vector<Edge>& edge_pq, std::vector<bool>& marked) {
    for (const auto& edge : graph.AdjacentEdges(vertex)) {
        if (not marked[edge.to]) {
            edge_pq.emplace_back(edge.from, edge.to, edge.weight);
            heap::PushHeap(begin(edge_pq), end(edge_pq), EdgeComp);
        }
    }
}

}  // anonymous namespace

/**
 * Prim's MST algorithm
 */
std::vector<Edge> Prim(const UndirectedWeightedGraph& graph) {
    std::vector<bool> marked(graph.VertexSize(), false);
    std::vector<Edge> result, edge_pq;
    AddVertex(graph, 0, edge_pq, marked);
    marked[0] = true;
    for (; result.size() != graph.VertexSize() - 1;) {
        // get shortest edge
        heap::PopHeap(begin(edge_pq), end(edge_pq), EdgeComp);
        Edge edge = edge_pq.back();
        edge_pq.pop_back();

        // try to add v1 or v2
        if (not marked[edge.v1]) {
            AddVertex(graph, edge.v1, edge_pq, marked);
            marked[edge.v1] = true;
            result.push_back(edge);
        } else if (not marked[edge.v2]) {
            AddVertex(graph, edge.v2, edge_pq, marked);
            marked[edge.v2] = true;
            result.push_back(edge);
        }
    }
    return result;
}

/**
 * Kruskal's MST algorithm
 */
std::vector<Edge> Kruskal(const UndirectedWeightedGraph& graph) {
    // get all edges
    std::vector<Edge> edges = ExtractEdge(graph), result;
    UnionFind<Graph::Vertex> uf;
    heap::Heapify(begin(edges), end(edges), EdgeComp);

    for (; not edges.empty();) {
        heap::PopHeap(begin(edges), end(edges), EdgeComp);
        Edge edge = edges.back();
        edges.pop_back();
        if (not uf.Connected(edge.v1, edge.v2)) {
            result.push_back(edge);
            uf.Connect(edge.v1, edge.v2);
        }
    }
    return result;
}

}  // namespace mst(minimum spanning tree)

}  // namespace graph

}  // namespace vinalx

#endif
