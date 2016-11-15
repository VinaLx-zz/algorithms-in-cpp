#ifndef INSERTIONSORT_HPP_
#define INSERTIONSORT_HPP_

namespace vinalx {

class InsertionSort {
  public:
    // insertion Sort only for bidirectional iterator
    template <typename BidIter>
    static void Sort(BidIter beg, BidIter end) {
        auto current = beg;
        BidIter front, behind;
        for (; ++current != end;) {
            front = current;
            behind = front--;
            auto element = *current;
            for (; element < *front;) {
                *behind-- = *front;
                if (front == beg)
                    break;
                --front;
            }
            *behind = element;
        }
    }
};

} // namespace vinalx

#endif
