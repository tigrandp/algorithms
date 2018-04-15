#include "sorting.h"

#include <algorithm>
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

void RecursiveQuickSort(
    Iterator begin, Iterator end,
    const std::function<Iterator(Iterator, Iterator)>& partition_func) {
  std::size_t length = std::distance(begin, end);
  if (length <= 1) return;

  Iterator pivot_it = partition_func(begin, end);
  RecursiveQuickSort(begin, pivot_it, partition_func);
  RecursiveQuickSort(std::next(pivot_it), end, partition_func);
}

}  // namespace

void StandardSort(Iterator begin, Iterator end) { std::sort(begin, end); }

void HoarPartitionSort(Iterator begin, Iterator end) {
  StandardSort(begin, end);
}

void SimplePartitionSort(Iterator begin, Iterator end) {
  RecursiveQuickSort(begin, end, SimplePartitionFunction);
}

void IndistinctPartitionSort(Iterator begin, Iterator end) {
  StandardSort(begin, end);
}

void HoarRandomPartitionSort(Iterator begin, Iterator end) {
  StandardSort(begin, end);
}

void SimpleRandomPartitionSort(Iterator begin, Iterator end) {
  StandardSort(begin, end);
}
