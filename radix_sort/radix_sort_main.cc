#include "radix_sort.h"
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

constexpr int32_t MAXN = 10000000;

int32_t a[MAXN];
int32_t b[MAXN];

int main() {
  srand(time(NULL));
  for (int i = 0; i < MAXN; ++i) {
    b[i] = a[i] = rand() % 1000;
  }

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  RadixSort(a, a + MAXN);
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << 1e-6 * duration << endl;

  t1 = high_resolution_clock::now();
  sort(b, b + MAXN);
  t2 = high_resolution_clock::now();
  duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << 1e-6 * duration << endl;

  return 0;
}
