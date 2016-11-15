#ifndef QUICKSORT_HPP_
#define QUICKSORT_HPP_

#include "InsertionSort.hpp"
#include <utility>

namespace vinalx {

class QuickSort {
  public:
    template <typename RAIter>
    static void Sort(RAIter beg, RAIter end) {
        if (end <= beg) {
            return;
        }
        if (end - beg < threshold) {
            InsertionSort::Sort(beg, end);
            return;
        }
        RAIter pivot = partition(beg, end);
        Sort(beg, pivot);
        Sort(pivot + 1, end);
    }

  private:
    static const int threshold = 16;

    template <typename RAIter>
    static RAIter partition(RAIter beg, RAIter end) {
        auto left_iter = beg, right_iter = end - 1;
        auto pivot_value = *left_iter++;
        for (;;) {
            for (; left_iter != end and pivot_value >= *left_iter;)
                ++left_iter;
            for (; right_iter != beg and pivot_value < *right_iter;)
                --right_iter;
            if (left_iter >= right_iter) {
                std::swap(*beg, *right_iter);
                return right_iter;
            }
            std::swap(*left_iter, *right_iter);
        }
    }
};

} // namespace vinalx

#endif
