#ifndef HEAP_HPP_
#define HEAP_HPP_

#include <cassert>
#include <functional>
#include <iterator>
#include <utility>  // std::swap
#include <vector>

namespace vinalx {

using std::size_t;

namespace heap {

namespace {

#define LEFT_NODE(offset) (offset * 2 + 1)
#define RIGHT_NODE(offset) ((offset + 1) * 2)
#define PARENT_NODE(offset) ((offset - 1) / 2)

template <typename Iter>
auto GetElemHelper(Iter start) {
    return [start](typename Iter::difference_type offset) ->
           typename Iter::value_type& {
        return *std::next(start, offset);
    };
}

template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
void Sink(
    Iter start, Iter finish, Comp cmp = Comp(),
    typename Iter::difference_type target = -1) {
    typename Iter::difference_type current = target == -1 ? 0 : target,
                                   stop = std::distance(start, finish);
    auto GetElem = GetElemHelper(start);
    for (;;) {
        auto left = LEFT_NODE(current), right = RIGHT_NODE(current);
        decltype(current) bigger;
        if (not(left < stop)) {
            return;
        }
        if (not(right < stop)) {
            bigger = left;
        } else {
            bigger = cmp(GetElem(left), GetElem(right)) ? right : left;
        }
        if (cmp(GetElem(current), GetElem(bigger))) {
            std::swap(GetElem(current), GetElem(bigger));
            current = bigger;
        } else {
            return;
        }
    }
}

template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
void Swim(Iter top, Iter tail, Comp cmp = Comp()) {
    typename Iter::difference_type current = std::distance(top, tail), stop = 0;
    auto GetElem = GetElemHelper(top);
    for (;;) {
        auto parent = PARENT_NODE(current);
        if (cmp(GetElem(parent), GetElem(current))) {
            std::swap(GetElem(parent), GetElem(current));
            current = parent;
        } else {
            return;
        }
        if (parent == 0) {
            return;
        }
    }
}

}  // anonymous namespace

/**
 * push the last element in the range to the heap
 */
template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
void PushHeap(Iter start, Iter finish, Comp cmp = Comp()) {
    if (start == finish) {
        return;
    }
    Swim(start, std::prev(finish), cmp);
}

/**
 * heapify the range specified
 */
template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
void Heapify(Iter start, Iter finish, Comp cmp = Comp()) {
    for (Iter current = std::next(start); current != finish;) {
        PushHeap(start, current, cmp);
        std::advance(current, 1);
    }
}

/**
 * move the first element from the end of the range
 * and maintain the rest as a heap
 * @return return the iterator point to the popped element
 */
template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
Iter PopHeap(Iter start, Iter finish, Comp cmp = Comp()) {
    if (start == finish) {
        return finish;
    }
    std::iter_swap(start, std::prev(finish));
    Sink(start, prev(finish), cmp);
    return prev(finish);
}

/**
 * determine whether the range is a heap
 */
template <typename Iter, typename Comp = std::less<typename Iter::value_type>>
bool IsHeap(Iter start, Iter finish, Comp cmp = Comp()) {
    auto GetElem = GetElemHelper(start);
    for (typename Iter::difference_type current = 0,
                                        stop = std::distance(start, finish);
         ; ++current) {
        auto left = LEFT_NODE(current), right = RIGHT_NODE(current);
        if (not(left < stop)) {
            break;
        }
        if (cmp(GetElem(current), GetElem(left))) {
            return false;
        }
        if (right < stop) {
            if (cmp(GetElem(current), GetElem(right))) {
                return false;
            }
        } else {
            break;
        }
    }
    return true;
}

#undef LEFT_NODE
#undef RIGHT_NODE
#undef PARENT_NODE

/**
 * priority queue
 */
template <typename T, typename Comp = std::less<T>>
class Heap {
  public:
    template <typename Iter>
    Heap(Iter start, Iter finish, Comp compare = Comp())
    : heap_(start, finish), compare_(compare) {
        Heapify(begin(heap_), end(heap_), compare_);
    }

    Heap(Comp compare = Comp()): compare_(compare) {}

    void Push(const T& elem) {
        heap_.push_back(elem);
        PushHeap(begin(heap_), end(heap_), compare_);
    }

    T Pop() {
        T ret = *PopHeap(begin(heap_), end(heap_), compare_);
        heap_.pop_back();
        return ret;
    }

    size_t Size() const {
        return heap_.size();
    }

    const std::vector<T>& Data() const {
        return heap_;
    }

  private:
    std::vector<T> heap_;
    Comp compare_;
};

}  // namespace heap

}  // namespace vinalx

#endif  // HEAP_H_
