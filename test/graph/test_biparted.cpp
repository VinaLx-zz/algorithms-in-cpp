#include "graph/IsBiparted.hpp"
#include <gtest/gtest.h>

using vinalx::graph::UndirectedUnweightedGraph;
using vinalx::graph::IsBiparted;

class TestBiparted: public ::testing::Test {
    protected:
        void SetUp() {
            graph0 = UndirectedUnweightedGraph(2);
            graph0.AddEdge(0,1);
            graph1 = UndirectedUnweightedGraph(9);
            graph1.AddEdge(1,2);
            graph1.AddEdge(2,3);
            graph1.AddEdge(3,4);
            graph1.AddEdge(0,1);
            graph1.AddEdge(1,5);
            graph1.AddEdge(5,7);
            graph1.AddEdge(0,8);
            graph1.AddEdge(8,4);
            graph1.AddEdge(5,6);
            graph1.AddEdge(6,4);
            graph2 = UndirectedUnweightedGraph(5);
            graph2.AddEdge(0,1);
            graph2.AddEdge(1,4);
            graph2.AddEdge(4,2);
            graph2.AddEdge(1,2);
            graph2.AddEdge(2,3);
        }

        UndirectedUnweightedGraph graph0, graph1, graph2;
        
};


TEST_F(TestBiparted, Graph0Test) {
    EXPECT_TRUE(IsBiparted(graph0));
}

TEST_F(TestBiparted, Graph1Test) {
    EXPECT_TRUE(IsBiparted(graph1));
}

TEST_F(TestBiparted, Graph2Test) {
    EXPECT_FALSE(IsBiparted(graph2));
}
