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

template <typename Tree, typename Container>
void TestInsert(Tree& bst, Container cont) {
    bst.Clear();
    cont.erase(std::unique(begin(cont), end(cont)), end(cont));
    ASSERT_TRUE(bst.Size() == 0);
    size_t count = 0;
    for (auto& value : cont) {
        EXPECT_FALSE(bst.Has(value));
        bst.Insert(value);
        EXPECT_TRUE(bst.Has(value));
        ++count;
        EXPECT_EQ(count, bst.Size());
        EXPECT_TRUE(CheckSorted(bst));
    }
}

template <typename Tree, typename Container>
void TestErase(Container cont) {
    cont.erase(std::unique(begin(cont), end(cont)), end(cont));
    auto bst = InitWith<Tree>(cont);
    ASSERT_EQ(bst.Size(), cont.size());
    size_t size = bst.Size();
    for (auto value : cont) {
        ASSERT_TRUE(bst.Has(value));
        bst.Erase(value);
        --size;
        EXPECT_EQ(size, bst.Size());
        EXPECT_FALSE(bst.Has(value));
        EXPECT_TRUE(CheckSorted(bst));
    }
}

vector<int> NonDuplicateInt(size_t size = 500) {
    vector<int> ret(size);
    std::generate(begin(ret), end(ret), []() {
        static int v = 0;
        return v++;
    });
    std::shuffle(begin(ret), end(ret), std::random_device());
    return ret;
}

template <typename Bst>
class BstTest : public testing::Test {};

using TreeTypes = testing::Types<BinarySearchTree<int>, AvlTree<int>>;

TYPED_TEST_CASE(BstTest, TreeTypes);

TYPED_TEST(BstTest, SimpleInsertTest) {
    TypeParam bst;
    TestInsert(bst, vector<int>{1, 2});
}

TYPED_TEST(BstTest, InsertTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    TypeParam bst;
    TestInsert(bst, values);
}

TYPED_TEST(BstTest, RandomInsertTest) {
    TypeParam bst;
    for (int i = 0; i < 100; ++i) {
        TestInsert(bst, NonDuplicateInt());
    }
}

TYPED_TEST(BstTest, EraseTest) {
    vector<int> values{6, 4, 8, 9, 1, 0, 3, 5, 7, 2};
    TestErase<TypeParam>(values);
}

TYPED_TEST(BstTest, EraseTest2) {
    vector<int> values{1, 4, 7, 2, 5, 8, 9, 0, 10, 6, 13};
    TestErase<TypeParam>(values);
}

TYPED_TEST(BstTest, RandomEraseTest) {
    for (int i = 0; i < 100; ++i) {
        TestErase<TypeParam>(NonDuplicateInt());
    }
}
