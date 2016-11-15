#ifndef SELECTIONSORT_HPP_
#define SELECTIONSORT_HPP_

#include <utility>

namespace vinalx {

class SelectionSort {
  public:
    template <typename FwdIter>
    static void Sort(FwdIter beg, FwdIter end) {
        FwdIter min_iter, check_iter;
        for (auto now = beg; now != end; ++now) {
            for (min_iter = check_iter = now; check_iter != end; ++check_iter) {
                if (*check_iter < *min_iter)
                    min_iter = check_iter;
            }
            std::swap(*min_iter, *now);
        }
    }
};

} // namespace vinalx
#endif
