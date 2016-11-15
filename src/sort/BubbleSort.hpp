#ifndef BUBBLESORT_HPP_
#define BUBBLESORT_HPP_

#include <cstdint>
#include <iostream>
#include <iterator> // std::iterator_traits
#include <utility>  // std::swap

namespace vinalx {

class BubbleSort {
  public:
    template <typename Iter>
    static void Sort(Iter beg, Iter end) {
        if (beg == end)
            return;
        Sort(beg, end,
                 typename std::iterator_traits<Iter>::iterator_category());
    }

  private:
    template <typename FwdIter>
    static void Sort(FwdIter beg, FwdIter end,
                         std::forward_iterator_tag) {
        uint64_t size{0};
        auto next = beg, prev = next;
        for (; ++next != end;) {
            if (*next < *prev)
                std::swap(*next, *prev);
            ++size;
            ++prev;
        }
        for (auto i = size - 1; i > 0; --i) {
            next = beg;
            prev = next++;
            for (auto j = i; j > 0; --j) {
                if (*next < *prev)
                    std::swap(*next, *prev);
                ++next;
                ++prev;
            }
        }
    }

    /*  // this version somehow even slower than Forward Iterator version

        template <typename BidIter>
        static void Sort(BidIter beg, BidIter end,
                             std::bidirectional_iterator_tag) {
            BidIter next, prev;
            for (; --end != beg;) {
                for (next = beg, prev = next++; prev != end;) {
                    if (*next < *prev)
                        std::swap(*next, *prev);
                    ++next;
                    ++prev;
                }
            }
        }
    */

    template <typename RAIter>
    static void Sort(RAIter beg, RAIter end,
                         std::random_access_iterator_tag) {
        auto size = end - beg;
        RAIter prev, next;
        for (decltype(size) i = size - 1; i > 0; --i) {
            prev = beg;
            next = prev + 1;
            for (decltype(size) j = 0; j < i; ++j) {
                if (*next < *prev)
                    std::swap(*next, *prev);
                ++next;
                ++prev;
            }
        }
    }
};

} // namespace vinalx

#endif
