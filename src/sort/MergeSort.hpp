#ifndef MERGESORT_HPP_
#define MERGESORT_HPP_

#include "InsertionSort.hpp"
#include <algorithm> // std::copy
#include <vector>

namespace vinalx {

class MergeSort {
  public:
    template <typename RAIter>
    static void Sort(RAIter beg, RAIter end) {
        if (end - beg < threshold) {
            InsertionSort::Sort(beg, end);
            return;
        }

        RAIter mid_iter = beg + (end - beg) / 2;
        Sort(beg, mid_iter);
        Sort(mid_iter, end);
        merge(beg, mid_iter, end);
    }

  private:
    static const int threshold = 16;

    template <typename RAIter>
    static void merge(RAIter beg, RAIter mid, RAIter end) {
        std::vector<typename RAIter::value_type> v1(beg, mid),
            v2(mid, end);
        auto iter1 = v1.begin(), iter2 = v2.begin();
        for (; iter1 != v1.end() && iter2 != v2.end();) {
            if (*iter1 < *iter2)
                *beg++ = *iter1++;
            else
                *beg++ = *iter2++;
        }
        if (iter1 == v1.end())
            std::copy(iter2, v2.end(), beg);
        else
            std::copy(iter1, v1.end(), beg);
    }
};
}

#endif
