#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "tree/BinarySearchTree.hpp"

using vinalx::tree::BinarySearchTree;
using std::vector;

template <typename T>
vector<T> Traverse(const BinarySearchTree<T>& bst) {
    vector<T> result;
    bst.InorderTraverse([&result](const T& data) { result.push_back(data); });
    return result;
}

template <typename T>
bool CheckSorted(const BinarySearchTree<T>& bst) {
    vector<T> traverse_result = Traverse(bst);
    return std::is_sorted(begin(traverse_result), end(traverse_result));
}

template <typename T, typename Container>
BinarySearchTree<T> InitWith(const Container& cont) {
    BinarySearchTree<T> bst;
    for (const auto& v : cont) {
        bst.Insert(v);
    }
    return bst;
}

TEST(BstTest, SimpleInsertTest) {
    BinarySearchTree<int> bst;
    EXPECT_EQ(bst.Size(), 0);
    bst.Insert(1);
    EXPECT_EQ(bst.Size(), 1);
    bst.Insert(2);
    EXPECT_EQ(bst.Size(), 2);
    EXPECT_TRUE(bst.Has(2));
    EXPECT_TRUE(bst.Has(1));
    EXPECT_TRUE(CheckSorted(bst));
}

TEST(BstTest, InsertTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    BinarySearchTree<int> bst;
    for (auto v : values) {
        bst.Insert(v);
    }
    for (auto v : values) {
        EXPECT_TRUE(bst.Has(v));
    }
    EXPECT_TRUE(CheckSorted(bst));
}

TEST(BstTest, EraseTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    auto bst = InitWith<int>(values);
    int size = bst.Size();
    EXPECT_EQ(size, 10);
    for (auto v : values) {
        bst.Erase(v);
        --size;
        EXPECT_FALSE(bst.Has(v));
        EXPECT_TRUE(CheckSorted(bst));
        EXPECT_EQ(bst.Size(), size);
    }
    EXPECT_EQ(bst.Size(), 0);
}

TEST(BstTest, EraseTest2) {
    vector<int> values{1, 4, 7, 2, 5, 8, 9, 0, 10, 6, 13};
    auto bst = InitWith<int>(values);
    ASSERT_EQ(bst.Size(), 11);
    int size = bst.Size();
    for (auto v : values) {
        bst.Erase(v);
        EXPECT_FALSE(bst.Has(v));
        bst.Erase(v);
        --size;
        EXPECT_EQ(size, bst.Size());
        EXPECT_TRUE(CheckSorted(bst));
    }
    EXPECT_EQ(bst.Size(), 0);
}
