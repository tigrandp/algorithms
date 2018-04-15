#include <vector>

// Sort the given range using std::sort.
void StandardSort(std::vector<int>::iterator begin,
                  std::vector<int>::iterator end);

// Sort the given range using quick sort with Hoar partition.
void HoarPartitionSort(std::vector<int>::iterator begin,
                       std::vector<int>::iterator end);

// Sort the given range using simple in-place partition.
void SimplePartitionSort(std::vector<int>::iterator begin,
                         std::vector<int>::iterator end);

// Sort the given range using simple in-place partition, but specifically take
// care of repeatitions.
void IndistinctPartitionSort(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end);

// Sort the given range using Hoar's partition with choosing random pivot.
void HoarRandomPartitionSort(std::vector<int>::iterator begin,
                             std::vector<int>::iterator end);

// Sort the given range using simple in-place partition with choosing random
// pivot.
void SimpleRandomPartitionSort(std::vector<int>::iterator begin,
                               std::vector<int>::iterator end);
