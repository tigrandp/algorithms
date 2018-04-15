#include "sorting.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iterator>

namespace {

Iterator Advance(Iterator it, std::size_t distance) {
  return it + distance;
}

Iterator SimplePartitionFunction(Iterator begin, Iterator end) {
  int pivot = *std::prev(end);
  int i = -1;
  for (Iterator it = begin; std::next(it) != end; it = std::next(it)) {
    if (*it <= pivot) {
      ++i;
      std::swap(*Advance(begin, i), *it);
    }
  }
  std::swap(*Advance(begin, i + 1), *std::prev(end));

  return Advance(begin, i + 1);
}

Iterator HoarePartitionFunction(Iterator begin, Iterator end) {
  Iterator forward = begin;
  Iterator backward = std::prev(end);
  Iterator pivot = backward;

    while (backward != forward) {
      if (*backward < *pivot) {
        std::swap(*backward, *forward);
        forward = std::next(forward);
      } else {
        backward = std::prev(backward);
      }
    }
    if (*backward < *pivot) {
      backward = std::next(backward);
    }
      std::swap(*backward, *pivot);
      return backward;
}

void GetRandomPivot(Iterator begin, Iterator end) {
  std::size_t length = std::distance(begin, end);
  std::size_t pivot_index = std::rand() % length;
  std::swap(*std::prev(end), *Advance(begin, pivot_index));
}

Iterator RandomHoarePartitionFunction(Iterator begin, Iterator end) {
  GetRandomPivot(begin, end);
  return HoarePartitionFunction(begin, end);
}

Iterator RandomSimplePartitionFunction(Iterator begin, Iterator end) {
  GetRandomPivot(begin, end);
  return SimplePartitionFunction(begin, end);
}

void RecursiveQuickSort(
    Iterator begin, Iterator end,
    const std::function<Iterator(Iterator, Iterator)>& partition_func) {
  std::size_t length = std::distance(begin, end);
  if (length <= 1) return;

  Iterator pivot_it = partition_func(begin, end);
  RecursiveQuickSort(begin, pivot_it, partition_func);
  RecursiveQuickSort(std::next(pivot_it), end, partition_func);
}

void TailRecursionQuickSort(Iterator begin, Iterator end,
    const std::function<Iterator(Iterator, Iterator)>& partition_func) {
  while (std::distance(begin, end) > 0) {
    Iterator pivot_it = partition_func(begin, end);
    TailRecursionQuickSort(begin, pivot_it, partition_func);
    begin = std::next(pivot_it);
  }
}

std::pair<Iterator, Iterator> OptimizedPartition(Iterator begin, Iterator end) {
  Iterator forward = begin;
  Iterator backward = std::prev(end);
  Iterator pivot = backward;

    while (backward != forward) {
      if (*backward < *pivot) {
        std::swap(*backward, *forward);
        forward = std::next(forward);
      } else {
        backward = std::prev(backward);
      }
    }
    if (*backward < *pivot) {
      backward = std::next(backward);
    }
    std::swap(*backward, *pivot);
    Iterator left_pivot = backward;
    Iterator rigth_pivot = backward;

    if (left_pivot != begin) {
    backward = std::prev(left_pivot);
    while (true) {
      if (*backward == *left_pivot) {
        left_pivot = std::prev(left_pivot);
        if (&*backward != &*left_pivot) {
          std::swap(*backward, *left_pivot);
        }
      }
      if (backward == begin) break;
      backward = std::prev(backward);
    }
    }

    forward = std::next(rigth_pivot);
    while (forward != end) {
      if (*forward == *rigth_pivot) {
        rigth_pivot = std::next(rigth_pivot);
        if (&*forward != &*rigth_pivot) {
          std::swap(*forward, *rigth_pivot);
        }
      }
      forward = std::next(forward);
    }

    return {left_pivot, std::next(rigth_pivot)};
}

}  // namespace

void OptimizedQuickSort(Iterator begin, Iterator end) {
  if (std::is_sorted(begin, end)) return;
  std::size_t dist = std::distance(begin, end);
  if (dist <= 2) {
    std::vector<int> v(begin, end);
    std::make_heap(v.begin(), v.end(), std::greater<int>());
    for (auto it = begin; it != end; ++it) {
      *it = v[0];
      std::pop_heap(v.begin(), v.end());
    }
    return;
  }
  while (std::distance(begin, end) > 0) {
    GetRandomPivot(begin, end);
    auto its = OptimizedPartition(begin, end);
    OptimizedQuickSort(begin, its.first);
    begin = its.second;
  }
}

void StandardSort(Iterator begin, Iterator end) { std::sort(begin, end); }

void HoarPartitionSort(Iterator begin, Iterator end) {
  RecursiveQuickSort(begin, end, HoarePartitionFunction);
}

void SimplePartitionSort(Iterator begin, Iterator end) {
  RecursiveQuickSort(begin, end, SimplePartitionFunction);
}

void HoarRandomPartitionSort(Iterator begin, Iterator end) {
  RecursiveQuickSort(begin, end, RandomHoarePartitionFunction);
}

void SimpleRandomPartitionSort(Iterator begin, Iterator end) {
  RecursiveQuickSort(begin, end, RandomSimplePartitionFunction);
}

void HoareTailRecursionSort(Iterator begin, Iterator end) {
  TailRecursionQuickSort(begin, end, RandomHoarePartitionFunction);
}
