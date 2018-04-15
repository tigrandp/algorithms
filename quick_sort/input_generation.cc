#include "input_generation.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace {

int GetRandomNumber() {
  static bool initialized_rand = false;
  if (!initialized_rand) {
    std::srand(std::time(0));
  }

  return std::rand();
}

}  // namespace

std::vector<int> GenerateRandomSequence(std::size_t sequence_size) {
  std::vector<int> data;
  data.reserve(sequence_size);
  for (std::size_t it = 0; it < sequence_size; ++it) {
    data.push_back(GetRandomNumber());
  }

  return data;
}

std::vector<int> GenerateSortedSequence(std::size_t sequence_size) {
  std::vector<int> data = GenerateRandomSequence(sequence_size);
  std::sort(data.begin(), data.end());

  return data;
}

std::vector<int> GenerateReverseSortedSequence(std::size_t sequence_size) {
  std::vector<int> data = GenerateSortedSequence(sequence_size);
  std::reverse(data.begin(), data.end());

  return data;
}

std::vector<int> GenerateSameElementsSequence(std::size_t sequence_size) {
  // 80 percent
  std::size_t same_element_count = sequence_size * 0.8;
  std::vector<int> data =
      GenerateRandomSequence(sequence_size - same_element_count);
  int number = GetRandomNumber();
  for (std::size_t it = 0; it < same_element_count; ++it) {
    data.push_back(number);
  }
  std::random_shuffle(data.begin(), data.end());

  return data;
}
