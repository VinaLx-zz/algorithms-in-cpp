#ifndef HEAP_H
#define HEAP_H

#include <cassert>
#include <type_traits>
#include <utility>  // std::swap
#include <vector>

namespace vinalx {

using std::size_t;

template <typename T>
class Heap {
    std::vector<T> data_;

  public:
    template <typename FwdIter,
              typename = typename std::enable_if<std::is_convertible<
                  typename FwdIter::value_type, T>::value>::type>
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
#endif

#ifdef VINALX_DEBUG
    std::vector<T> &Data() {
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
};

}  // namespace vinalx

#endif
