#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

// int*** обращается к температуре по городу, дню и времени измерения.
// void* хранит общий блок; программа считает среднее по каждому городу.
int main() {
  constexpr int cMeasurementsPerDay = 3;

  int city_count;
  int day_count;
  if (!(std::cin >> city_count >> day_count) || city_count <= 0 ||
      day_count <= 0) {
    std::cout << "error\n";
    return 1;
  }

  const std::size_t cCitySize = static_cast<std::size_t>(city_count);
  const std::size_t cDaySize = static_cast<std::size_t>(day_count);
  const std::size_t cMaximumSize = std::numeric_limits<std::size_t>::max();
  if (cCitySize > cMaximumSize / cDaySize ||
      cCitySize * cDaySize >
          cMaximumSize / cMeasurementsPerDay / sizeof(int)) {
    std::cout << "error\n";
    return 1;
  }

  const std::size_t cValueCount = cCitySize * cDaySize * cMeasurementsPerDay;
  void* buffer = std::malloc(cValueCount * sizeof(int));
  if (buffer == nullptr) {
    std::cout << "error\n";
    return 1;
  }

  int* values = static_cast<int*>(buffer);
  int*** temperatures = new int**[city_count];
  for (int city = 0; city < city_count; ++city) {
    temperatures[city] = new int*[day_count];
    for (int day = 0; day < day_count; ++day) {
      const std::size_t cFirstValue =
          (static_cast<std::size_t>(city) * cDaySize + day) *
          cMeasurementsPerDay;
      temperatures[city][day] = values + cFirstValue;
    }
  }

  bool input_is_valid = true;
  for (int city = 0; city < city_count && input_is_valid; ++city) {
    for (int day = 0; day < day_count && input_is_valid; ++day) {
      for (int time = 0; time < cMeasurementsPerDay; ++time) {
        if (!(std::cin >> temperatures[city][day][time])) {
          input_is_valid = false;
          break;
        }
      }
    }
  }

  if (input_is_valid) {
    std::cout << std::fixed << std::setprecision(1);
    for (int city = 0; city < city_count; ++city) {
      long long sum = 0;
      for (int day = 0; day < day_count; ++day) {
        for (int time = 0; time < cMeasurementsPerDay; ++time) {
          sum += temperatures[city][day][time];
        }
      }

      const std::size_t cCityValueCount = cDaySize * cMeasurementsPerDay;
      std::cout << "City " << city + 1 << ": "
                << static_cast<double>(sum) / cCityValueCount << '\n';
    }
  } else {
    std::cout << "error\n";
  }

  for (int city = 0; city < city_count; ++city) {
    delete[] temperatures[city];
  }
  delete[] temperatures;
  std::free(buffer);

  return input_is_valid ? 0 : 1;
}
