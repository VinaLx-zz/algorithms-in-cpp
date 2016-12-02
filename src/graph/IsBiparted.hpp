#ifndef IS_BIPARTED_HPP_
#define IS_BIPARTED_HPP_

#include "UndirectedUnweightedGraph.hpp"

namespace vinalx {
namespace graph {

namespace {

enum Color { NONE = 0, BLACK = -1, RED = 1 };

std::vector<Color> color;

Color GetAnotherColor(Color c) {
    if (c == BLACK) {
        return RED;
    } else if (c == RED) {
        return BLACK;
    }
    return NONE;
}

bool Dfs(const UndirectedUnweightedGraph& graph, size_t start) {
    auto adjacent_vertices = graph.AdjacentTo(start);
    for (auto adj : adjacent_vertices) {
        if (not color[adj]) {
            color[adj] = GetAnotherColor(color[start]);;
            if (not Dfs(graph, start)) {
                return false;
            }
        } else if (color[adj] != color[start]) {
            return false;
        }
    }
    return true;
}

}  // anonymous namespace

bool IsBiparted(const UndirectedUnweightedGraph& graph) {
    color.assign(graph.VertexSize(), Color::NONE);
    for (size_t i = 0; i < graph.VertexSize(); ++i) {
        if (not color[i]) {
            color[i] = BLACK;
            if (not Dfs(graph, i)) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace graph
}  // namespace vinalx

#endif  // IS_BIPARTED_HPP_
