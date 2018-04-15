#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iomanip>
#include <sstream>
#include <utility>
#include <vector>

#include "input_generation.h"
#include "sorting.h"

namespace {

double MeasureSortRunTime(
    std::vector<int>::iterator begin, std::vector<int>::iterator end,
    const std::function<void(std::vector<int>::iterator,
                             std::vector<int>::iterator)>& sort_function) {
  // fprintf(stderr, "Before: ");
  // for (auto it = begin; it != end; ++it) {
  //  fprintf(stderr, "%d ", *it);
  //}
  // fprintf(stderr, "\n");
  std::chrono::high_resolution_clock::time_point before =
      std::chrono::high_resolution_clock::now();
  sort_function(begin, end);
  std::chrono::high_resolution_clock::time_point after =
      std::chrono::high_resolution_clock::now();
  bool sorted = std::is_sorted(begin, end);
  if (!sorted) {
    fprintf(stderr, "Violation: ");
    for (auto it = begin; it != end; ++it) {
      fprintf(stderr, "%d ", *it);
    }
    fprintf(stderr, "\n");
  }
  assert(sorted);
  auto now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::ostringstream out;
  out << now;
  fprintf(stderr, "Heartbeat %s\n", out.str().c_str());
  return std::chrono::duration_cast<std::chrono::microseconds>(after - before)
             .count() /
         1000.0;
}

std::vector<std::pair<int, double>> GetSortStats(
    const std::string& input_type,
    const std::function<void(std::vector<int>::iterator,
                             std::vector<int>::iterator)>& sort_function) {
  std::function<std::vector<int>(int)> input_generator;
  if (input_type == "random") {
    input_generator = GenerateRandomSequence;
  } else if (input_type == "sorted") {
    input_generator = GenerateSortedSequence;
  } else if (input_type == "reverse_sorted") {
    input_generator = GenerateReverseSortedSequence;
  } else if (input_type == "same_elements") {
    input_generator = GenerateSameElementsSequence;
  } else {
    fprintf(stderr, "Unknown generator name: %s\n", input_type.c_str());
    assert(false && "Unknown generator name");
  }
  std::srand(889);
  fprintf(stderr, "Input type: %s\n", input_type.c_str());
  std::vector<std::pair<int, double>> run_stats;
  for (std::size_t sequence_size = 1000; sequence_size <= 100000;
       sequence_size += 5000) {
    auto sequence = input_generator(sequence_size);
    double run_time =
        MeasureSortRunTime(sequence.begin(), sequence.end(), sort_function);
    run_stats.push_back({sequence_size, run_time});
  }
  return run_stats;
}

void DumpStatsInFile(const std::vector<std::pair<int, double>>& stats,
                     const std::string& filename) {
  std::FILE* file = std::fopen(filename.c_str(), "w");
  if (file == nullptr) {
    fprintf(stderr, "Can not open file: %s\n", filename.c_str());
    assert(false);
  }
  for (const auto& entry : stats) {
    fprintf(file, "%d %.2lf\n", entry.first, entry.second);
  }
  std::fclose(file);
}

void ExecuteAndRecordSortStats() {
  std::vector<
      std::pair<std::string, std::function<void(std::vector<int>::iterator,
                                                std::vector<int>::iterator)>>>
      sorting_methods = {
          {"standard", StandardSort},
          //{"hoar_partition", HoarPartitionSort},
          //{"simple_partition", SimplePartitionSort},
          //{"hoar_random_partition", HoarRandomPartitionSort},
          //{"simple_random_partition", SimpleRandomPartitionSort},
          //{"tail_recursion", HoareTailRecursionSort},
          {"optimized", OptimizedQuickSort}};
  std::vector<std::string> input_types = {"random", "sorted", "reverse_sorted",
                                          "same_elements"};

  for (const std::string& input_type : input_types) {
    std::string filename_prefix = input_type + "/";
    for (const auto& method : sorting_methods) {
      std::string filename = filename_prefix + method.first + ".txt";
      const auto& sort_stats = GetSortStats(input_type, method.second);
      DumpStatsInFile(sort_stats, filename);
    }
  }
}

}  // namespace

int main(int argc, char* argv[]) {
  ExecuteAndRecordSortStats();

  return 0;
}
