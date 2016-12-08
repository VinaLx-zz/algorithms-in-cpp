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
    Sink(start, prev(finish));
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

template <typename T>
class Heap {
  public:
    template <typename FwdIter>
    Heap(FwdIter begin, FwdIter end) : data_(begin, end) {
        Heapify();
    }

    Heap() {}

  public:
#ifdef VINALX_DEBUG
    bool IsHeap() {
        for (size_t i{data_.size() - 1}; i > 0; --i) {
            if (data_[i] > data_[parent(i)])
                return false;
        }
        return true;
    }

    std::vector<T>& Data() {
        return data_;
    }
#endif

    void Heapify() {
        for (size_t i{1}; i < data_.size(); ++i) {
            Swim(i);
        }
    }

    void Push(T p_value) {
        data_.push_back(p_value);
        Swim(data_.size() - 1);
    }

    void Pop() {
        data_.front() = data_.back();
        data_.pop_back();
        Sink(0);
    }

    T Top() const {  // max
        return data_.at(0);
    }

    void Sort() {
#ifdef VINALX_DEBUG
        assert(IsHeap());
#endif
        for (size_t boundary{data_.size() - 1}; boundary > 0;) {
            std::swap(data_.front(), data_[boundary]);
            Sink(0, --boundary);
        }
    }

    bool Empty() const {
        return data_.empty();
    }

    void Clear() {
        data_.clear();
    }

  private:
    static size_t left(size_t parent) {
        return parent * 2 + 1;
    }
    static size_t right(size_t parent) {
        return (parent + 1) * 2;
    }
    static size_t parent(size_t leaf) {
        return (leaf - 1) / 2;
    }

    void Sink(const size_t target) {
        Sink(target, data_.size() - 1);
    }

    void Swim(const size_t target) {
        Swim(target, 0);
    }

    void Sink(const size_t target, const size_t bottom) {
        if (target >= bottom)
            return;
        T sinker{data_[target]};
        size_t current{target};
        for (T max_leaf; left(current) <= bottom;) {
            size_t max_index;
            if (right(current) > bottom or
                data_[right(current)] < data_[left(current)])
                max_index = left(current);
            else
                max_index = right(current);
            max_leaf = data_[max_index];
            if (sinker < max_leaf) {
                data_[current] = max_leaf;
                current = max_index;
            } else {
                break;
            }
        }
        data_[current] = sinker;
    }

    void Swim(const size_t target, const size_t top) {
        if (target <= top)
            return;
        T swimmer{data_[target]};
        size_t current{target};
        for (; current > top;) {
            if (swimmer > data_[parent(current)]) {
                data_[current] = data_[parent(current)];
                current = parent(current);
            } else {
                break;
            }
        }
        data_[current] = swimmer;
    }

  private:
    std::vector<T> data_;
};

}  // namespace heap

}  // namespace vinalx

#endif  // HEAP_H_
