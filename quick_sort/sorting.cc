#include "sorting.h"

#include <algorithm>

void StandardSort(std::vector<int>::iterator begin,
                  std::vector<int>::iterator end) {
  std::sort(begin, end);
}

void HoarPartitionSort(std::vector<int>::iterator begin,
                       std::vector<int>::iterator end) {}

void SimplePartitionSort(std::vector<int>::iterator begin,
                         std::vector<int>::iterator end) {}

void IndistinctPartitionSort(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end) {}

void HoarRandomPartitionSort(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end) {}

void SimpleRandomPartitionSort(std::vector<int>::iterator begin,
                               std::vector<int>::iterator end) {}
