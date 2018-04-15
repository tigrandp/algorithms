#include <vector>

using Iterator = std::vector<int>::iterator;

// Sort the given range using std::sort.
void StandardSort(Iterator begin, Iterator end);

// Sort the given range using quick sort with Hoar partition.
void HoarPartitionSort(Iterator begin, Iterator end);

// Sort the given range using simple in-place partition.
void SimplePartitionSort(Iterator begin, Iterator end);

// Sort the given range using simple in-place partition, but specifically take
// care of repeatitions.
void IndistinctPartitionSort(Iterator begin, Iterator end);

// Sort the given range using Hoar's partition with choosing random pivot.
void HoarRandomPartitionSort(Iterator begin, Iterator end);

// Sort the given range using simple in-place partition with choosing random
// pivot.
void SimpleRandomPartitionSort(Iterator begin, Iterator end);
