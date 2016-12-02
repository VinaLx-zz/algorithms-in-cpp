#include "graph/Cycle.hpp"
#include "graph/UnweightedGraph.hpp"
#include "gtest/gtest.h"

using vinalx::graph::UnweightedGraph;
using vinalx::graph::FindCycle;
using vinalx::graph::Graph;

class CycleTest : public ::testing::Test {
  protected:
    void SetUp() {
        graph_ = UnweightedGraph(5);
        ASSERT_EQ(graph_.VertexSize(), 5);
        graph_.AddEdge(0, 1);
        graph_.AddEdge(1, 2);
        graph_.AddEdge(2, 3);
        graph_.AddEdge(3, 4);
        graph_.AddEdge(4, 0);
        ASSERT_EQ(graph_.EdgeSize(), 5);
    }

    UnweightedGraph graph_;
};

TEST_F(CycleTest, BasicTest) {
    auto cycles = FindCycle(graph_);
    ASSERT_EQ(cycles.size(), 1);
    std::vector<Graph::Vertex> target_cycle{0, 1, 2, 3, 4};
    EXPECT_EQ(cycles.front(), target_cycle);
}

TEST_F(CycleTest, BasicTest2) {
    graph_.RemoveEdge(0, 1);
    EXPECT_FALSE(HasCycle(graph_));
    graph_.AddEdge(3, 1);
    EXPECT_TRUE(HasCycle(graph_));
}

TEST_F(CycleTest, MultipleCycle) {
    auto vertex1 = graph_.AddVertex(), vertex2 = graph_.AddVertex();
    graph_.AddEdge(vertex1, vertex2);
    graph_.AddEdge(vertex2, vertex1);
    auto cycles = FindCycle(graph_);
    EXPECT_EQ(cycles.size(), 2);
}
