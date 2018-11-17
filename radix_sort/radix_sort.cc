#include <cassert>
#include <iterator>
#include <list>

namespace {

constexpr int32_t kBinaryDigitLength = 16;
constexpr int32_t kTypeSize = sizeof(int32_t);
constexpr int32_t kNumberMask = (1 << kBinaryDigitLength) - 1;
std::list<int32_t> kBuckets[1 << kBinaryDigitLength];

void FillArray(const std::list<int32_t>& values, int32_t* output, int32_t& position) {
  for (int32_t x : values) {
    output[position++] = x;
  }
}

bool CountSort(int32_t* begin, int32_t n, int32_t num_shifts) {
  for (int32_t i = 0; i <= kNumberMask; ++i) {
    kBuckets[i].resize(0);
  }

  bool non_zero = false;
  for (int32_t i = 0; i < n; ++i) {
    int32_t raw_value = begin[i] >> (num_shifts * kBinaryDigitLength);
    if (raw_value != 0) {
      non_zero = true;
    }
    kBuckets[raw_value & kNumberMask].push_back(begin[i]);
  }

  if (!non_zero) return false;

  int32_t pos = 0;
  for (int32_t i = 0; i <= kNumberMask; ++i) {
    FillArray(kBuckets[i], begin, pos);
  }

  return true;
}

}  // namespace

void RadixSort(int32_t* begin, int32_t* end) {
  int32_t n = std::distance(begin, end);

  if (n <= 1) return;

  int32_t num_shifts = 0;
  while (CountSort(begin, n, num_shifts++)) {}
}
