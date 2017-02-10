#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "tree/AvlTree.hpp"
#include "tree/BinarySearchTree.hpp"

using vinalx::tree::BinarySearchTree;
using vinalx::tree::AvlTree;
using std::vector;

template <typename T, template <typename> class Tree>
vector<T> Traverse(const Tree<T>& bst) {
    vector<T> result;
    bst.InorderTraverse([&result](const T& data) { result.push_back(data); });
    return result;
}

template <typename T, template <typename> class Tree>
bool CheckSorted(const Tree<T>& bst) {
    vector<T> traverse_result = Traverse(bst);
    return std::is_sorted(begin(traverse_result), end(traverse_result));
}

template <typename Tree, typename Container>
Tree InitWith(const Container& cont) {
    Tree bst;
    for (const auto& v : cont) {
        bst.Insert(v);
    }
    return bst;
}

template <typename Bst>
class BstTest : public testing::Test {};

using TreeTypes = testing::Types<BinarySearchTree<int>, AvlTree<int>>;

TYPED_TEST_CASE(BstTest, TreeTypes);

TYPED_TEST(BstTest, SimpleInsertTest) {
    TypeParam bst;
    ASSERT_EQ(bst.Size(), 0);
    bst.Insert(1);
    ASSERT_EQ(bst.Size(), 1);
    ASSERT_TRUE(bst.Has(1)) << "After insert 1";
    bst.Insert(2);
    ASSERT_EQ(bst.Size(), 2);
    ASSERT_TRUE(bst.Has(2)) << "After insert 2";
    ASSERT_TRUE(bst.Has(1)) << "After insert 2";
    ASSERT_TRUE(CheckSorted(bst));
}

TYPED_TEST(BstTest, InsertTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    TypeParam bst;
    for (auto v : values) {
        bst.Insert(v);
        EXPECT_TRUE(bst.Has(v));
    }
    for (auto v : values) {
        EXPECT_TRUE(bst.Has(v));
    }
    EXPECT_TRUE(CheckSorted(bst));
}

TYPED_TEST(BstTest, EraseTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    auto bst = InitWith<TypeParam>(values);
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

TYPED_TEST(BstTest, EraseTest2) {
    vector<int> values{1, 4, 7, 2, 5, 8, 9, 0, 10, 6, 13};
    auto bst = InitWith<TypeParam>(values);
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
