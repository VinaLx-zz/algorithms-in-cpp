#include <gtest/gtest.h>
#include <climits>
#include "graph/ShortestPath.hpp"
#include "graph/UndirectedWeightedGraph.hpp"

using namespace vinalx::graph::shortest_path;
using vinalx::graph::Graph;
using vinalx::graph::UndirectedWeightedGraph;

class ShortestPathTest : public testing::Test {
  protected:
    void SetUp() {
        graph.AddEdge(1, 6, 4);
        graph.AddEdge(2, 1, 2);
        graph.AddEdge(1, 0, 3);
        graph.AddEdge(2, 0, 1);
        graph.AddEdge(0, 3, 1);
        graph.AddEdge(3, 4, 5);
        graph.AddEdge(3, 6, 1);
        graph.AddEdge(3, 5, 4);
        graph.AddEdge(2, 5, 3);
        graph.AddEdge(5, 6, 6);
    }
    UndirectedWeightedGraph graph = UndirectedWeightedGraph(8);
    int (*sp_algo)(const Graph&, Graph::Vertex, Graph::Vertex);

    void RunTest() {
        auto test = [this] (Graph::Vertex from, Graph::Vertex to) {
            return this->sp_algo(this->graph, from, to);
        };
        ASSERT_EQ(test(0, 6), 2);
        ASSERT_EQ(test(0, 5), 4);
        ASSERT_EQ(test(1, 3), 4);
        ASSERT_EQ(test(4, 6), 6);
    }

};

TEST_F(ShortestPathTest, TestDijkstra) {
    sp_algo = Dijkstra;
    RunTest();
}

TEST_F(ShortestPathTest, TestSpfa) {
    sp_algo = Spfa;
    RunTest();
}
