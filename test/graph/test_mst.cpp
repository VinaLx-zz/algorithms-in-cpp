#include <gtest/gtest.h>
#include "graph/MinimumSpanningTree.hpp"

using namespace vinalx::graph;

class MstTest : public testing::Test {
  protected:
    using MstAlgo = std::vector<mst::Edge> (*)(const UndirectedWeightedGraph&);
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

    void RunTest() {
        auto result = mst_algo(graph);
        int total_weight = 0;
        for (const auto& edge : result) {
            total_weight += edge.weight;
        }
        EXPECT_EQ(total_weight, 13);
    }
    UndirectedWeightedGraph graph = UndirectedWeightedGraph(7);
    MstAlgo mst_algo;
};

TEST_F(MstTest, TestPrim) {
    mst_algo = mst::Prim;
    RunTest();
}

TEST_F(MstTest, TestKruskal) {
    mst_algo = mst::Kruskal;
    RunTest();
}
