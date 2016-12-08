#include <gtest/gtest.h>
#include <vector>
#include "heap/Heap.hpp"

using std::vector;
using namespace vinalx;
using heap::IsHeap;

namespace {

template <typename Container>
typename Container::iterator PopHeap(Container& cont) {
    return heap::PopHeap(begin(cont), end(cont));
}

} // anonymous namespace


TEST(TestPopHeap, PopEmptyHeap) {
    vector<int> empty_heap{};
    auto iter = PopHeap(empty_heap);
    EXPECT_EQ(iter, end(empty_heap));
    EXPECT_EQ(empty_heap, vector<int>{});
}

TEST(TestPopHeap, PopSingleElem) {
    vector<int> single_elem{1};
    auto iter = PopHeap(single_elem);
    EXPECT_EQ(*iter, 1);
    EXPECT_EQ(single_elem, vector<int>{1});
}

TEST(TestPopHeap, PopSimpleHeap) {
    vector<int> double_elem{2, 1};
    vector<int> triple_elem{3, 2, 1};
    auto iter1 = PopHeap(double_elem);
    auto iter2 = PopHeap(triple_elem);
    EXPECT_EQ(*iter1, 2);
    EXPECT_EQ(*iter2, 3);
    EXPECT_TRUE(IsHeap(begin(double_elem), iter1));
    EXPECT_TRUE(IsHeap(begin(triple_elem), iter2));
}

TEST(TestPopHeap, PopLongHeap) {
    vector<int> long_heap1{10, 5, 8, 2, 4, 6, 7, 1, 0, 3};
    vector<int> long_heap2{100, 90, 50, 80, 81, 48, 49, 70,
                           71,  78, 79, 30, 20, 10, 5};
    auto iter1 = PopHeap(long_heap1);
    auto iter2 = PopHeap(long_heap2);
    EXPECT_EQ(*iter1, 10);
    EXPECT_EQ(*iter2, 100);
    EXPECT_TRUE(IsHeap(begin(long_heap1), iter1));
    EXPECT_TRUE(IsHeap(begin(long_heap2), iter2));
}
