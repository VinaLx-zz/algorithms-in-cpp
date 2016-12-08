#include <gtest/gtest.h>
#include <vector>
#include "heap/Heap.hpp"

using std::vector;
using namespace vinalx;
using heap::IsHeap;

namespace {

template <typename Container>
void PushHeap(Container& cont) {
    heap::PushHeap(begin(cont), end(cont));
}

template <typename Container>
bool IsHeap(Container& cont) {
    return heap::IsHeap(begin(cont), end(cont));
}

} // anonymous namespace

TEST(TestPushHeap, PushEmptyHeap) {
    vector<int> empty_heap{};
    PushHeap(empty_heap);
    EXPECT_EQ(empty_heap, vector<int>{});
}

TEST(TestPushHeap, PushSingleElem) {
    vector<int> single_elem{1};
    PushHeap(single_elem);
    EXPECT_EQ(single_elem, vector<int>{1});
}

TEST(TestPushHeap, SimplePushHeap) {
    vector<int> double_elem{1, 2};
    vector<int> double_elem2{2, 1};
    vector<int> triple_elem{2, 1, 3};
    PushHeap(double_elem);
    PushHeap(double_elem2);
    PushHeap(triple_elem);
    EXPECT_TRUE(IsHeap(double_elem));
    EXPECT_TRUE(IsHeap(double_elem2));
    EXPECT_TRUE(IsHeap(triple_elem));
}

TEST(TestPushHeap, PushLongHeap) {
    vector<int> long_heap1{10, 5, 8, 2, 4, 6, 7, 1, 0, 3};
    vector<int> long_heap2{100, 90, 50, 80, 81, 48, 49, 70,
                           71,  78, 79, 30, 20, 10, 5};
    long_heap1.push_back(100);
    long_heap2.push_back(82);
    PushHeap(long_heap1);
    PushHeap(long_heap2);
    EXPECT_TRUE(IsHeap(long_heap1));
    EXPECT_TRUE(IsHeap(long_heap2));
    long_heap1.push_back(40);
    long_heap2.push_back(50);
    PushHeap(long_heap1);
    PushHeap(long_heap2);
    EXPECT_TRUE(IsHeap(long_heap1));
    EXPECT_TRUE(IsHeap(long_heap2));
}
