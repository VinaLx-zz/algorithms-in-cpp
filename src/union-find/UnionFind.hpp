#ifndef UNION_FIND_HPP_
#define UNION_FIND_HPP_

#include <cstdint>
#include <unordered_map>
#include <vector>

namespace vinalx {

template <typename Vertex>
class UnionFind {
  private:
    /**
     * type of the index represents the vertex
     */
    using IndexType = size_t;

    /**
     * type of the rank
     */
    using RankType = int64_t;

  public:
    /**
     * connect two vertices
     */
    void Connect(const Vertex& vertex1, const Vertex& vertex2) {
        IndexType index1 = GetIndex(vertex1), index2 = GetIndex(vertex2);
        ConnectIndex(index1, index2);
    }

    /**
     * determine whether two vertices are connected
     */
    bool Connected(const Vertex& vertex1, const Vertex& vertex2) {
        if (not HaveIndex(vertex1) or not HaveIndex(vertex2)) {
            return false;
        }
        IndexType index1 = GetIndex(vertex1), index2 = GetIndex(vertex2);
        return RootOf(index1) == RootOf(index2);
    }

  private:
    /**
     * get the index of the vertex
     */
    IndexType GetIndex(const Vertex& vertex) {
        decltype(begin(index_map_)) result_iter;
        if ((result_iter = index_map_.find(vertex)) != end(index_map_)) {
            return result_iter->second;
        }
        IndexType index = index_map_[vertex] = parent_.size();
        parent_.push_back(index);
        rank_.push_back(1);
        return index;
    }

    /**
     * connect two index
     */
    void ConnectIndex(IndexType index1, IndexType index2) {
        IndexType root1 = RootOf(index1), root2 = RootOf(index2);
        if (root1 == root2) {
            return;
        }
        if (rank_[root1] < rank_[root2]) {
            parent_[root1] = root2;
        } else if (rank_[root1] > rank_[root2]) {
            parent_[root2] = root1;
        } else {
            parent_[root1] = root2;
            ++rank_[root2];
        }
    }

    /**
     * get the root Index of index
     */
    IndexType RootOf(IndexType index) {
        for (; index != parent_[index];) {
            index = parent_[index];
        }
        return index;
    }

    /**
     * whether the vertex has an index in the union-find
     */
    bool HaveIndex(const Vertex& vertex) const {
        return index_map_.find(vertex) != end(index_map_);
    }

    /**
     * map vertex to index
     */
    std::unordered_map<Vertex, IndexType> index_map_;

    /**
     * the parent of the index
     */
    std::vector<IndexType> parent_;

    /**
     * rank of the index
     */
    std::vector<RankType> rank_;
};

}  // namespace vinalx

#endif  // UNION_FIND_HPP_
