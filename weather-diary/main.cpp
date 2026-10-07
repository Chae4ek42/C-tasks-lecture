#include <iomanip>
#include <iostream>

struct TemperatureRange {
  int minimum;
  int maximum;
};

double AverageTemperature(const int* temperatures, int count) {
  long long sum = 0;
  for (int i = 0; i < count; ++i) {
    sum += temperatures[i];
  }
  return static_cast<double>(sum) / count;
}

TemperatureRange FindTemperatureRange(const int* temperatures, int count) {
  TemperatureRange range{temperatures[0], temperatures[0]};
  for (int i = 1; i < count; ++i) {
    if (temperatures[i] < range.minimum) {
      range.minimum = temperatures[i];
    }
    if (temperatures[i] > range.maximum) {
      range.maximum = temperatures[i];
    }
  }
  return range;
}

int CountFrostyDays(const int* temperatures, int count) {
  int frost_days = 0;
  for (int i = 0; i < count; ++i) {
    if (temperatures[i] < 0) {
      ++frost_days;
    }
  }
  return frost_days;
}

int main() {
  int count = 0;
  if (!(std::cin >> count) || count <= 0) {
    return 1;
  }

  int* temperatures = new int[count];
  for (int i = 0; i < count; ++i) {
    if (!(std::cin >> temperatures[i])) {
      delete[] temperatures;
      return 1;
    }
  }

  const double cAverage = AverageTemperature(temperatures, count);
  const TemperatureRange cRange = FindTemperatureRange(temperatures, count);
  const int cFrostDays = CountFrostyDays(temperatures, count);

  std::cout << std::fixed << std::setprecision(1) << cAverage << '\n';
  std::cout << cRange.minimum << ' ' << cRange.maximum << '\n';
  std::cout << cFrostDays << '\n';

  delete[] temperatures;
  return 0;
}
