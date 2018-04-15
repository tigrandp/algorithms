#include <cstddef>
#include <vector>

std::vector<int> GenerateRandomSequence(std::size_t sequence_size);
std::vector<int> GenerateSortedSequence(std::size_t sequence_size);
std::vector<int> GenerateReverseSortedSequence(std::size_t sequence_size);
// Generate sequence where at least 80% of all the elements are the same.
std::vector<int> GenerateSameElementsSequence(std::size_t sequence_size);
