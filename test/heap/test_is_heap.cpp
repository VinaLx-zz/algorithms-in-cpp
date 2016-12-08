#include <gtest/gtest.h>
#include "heap/Heap.hpp"

using std::vector;

namespace {
template <typename Container>
bool IsHeap(Container& cont) {
    return vinalx::heap::IsHeap(begin(cont), end(cont));
}
}

TEST(IsHeapTest, EmptySequence) {
    vector<int> empty_seq{};
    EXPECT_TRUE(IsHeap(empty_seq));
}

TEST(IsHeapTest, SingleElementTest) {
    vector<int> single_elem{1};
    EXPECT_TRUE(IsHeap(single_elem));
}

TEST(IsHeapTest, SimpleHeapTest) {
    vector<int> double_elem{2, 1};
    vector<int> triple_elem{3, 2, 1};
    EXPECT_TRUE(IsHeap(double_elem));
    EXPECT_TRUE(IsHeap(triple_elem));
}

TEST(IsHeapTest, SimpleNotHeapTest) {
    vector<int> double_elem{1, 2};
    vector<int> triple_elem{2, 3, 1};
    vector<int> triple_elem2{1, 3, 2};
    EXPECT_FALSE(IsHeap(double_elem));
    EXPECT_FALSE(IsHeap(triple_elem));
    EXPECT_FALSE(IsHeap(triple_elem2));
}

TEST(IsHeapTest, TestDuplicate) {
    vector<int> dup_elem{1,1};
    EXPECT_TRUE(IsHeap(dup_elem));
}

TEST(IsHeapTest, LongHeapTest) {
    vector<int> long_heap1{10, 5, 8, 2, 4, 6, 7, 1, 0, 3};
    vector<int> long_heap2{100, 90, 50, 80, 81, 48, 49, 70,
                           71,  78, 79, 30, 20, 10, 5};
    EXPECT_TRUE(IsHeap(long_heap1));
    EXPECT_TRUE(IsHeap(long_heap2));
}

TEST(IsHeapTest, LongNonHeapTest) {
    vector<int> long_heap1{1, 2, 3, 4, 5, 6, 7};
    vector<int> long_heap2{10, 5, 8, 2, 6, 4, 7, 8, 1, 0, 3};
    vector<int> long_heap3{100, 90, 50, 80, 81, 48, 49, 70,
                           71,  78, 79, 30, 20, 10, 75};
    vector<int> long_heap4{100, 90, 50, 80, 81, 48, 49, 70,
                           71,  85, 79, 30, 20, 10, 5};
    EXPECT_FALSE(IsHeap(long_heap1));
    EXPECT_FALSE(IsHeap(long_heap2));
    EXPECT_FALSE(IsHeap(long_heap3));
    EXPECT_FALSE(IsHeap(long_heap4));
}
