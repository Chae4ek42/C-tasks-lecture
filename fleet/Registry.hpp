#pragma once

#include <cstddef>
#include <utility>
#include <vector>

template <typename T>
class Registry {
 public:
  void Add(T item) { items_.push_back(std::move(item)); }

  std::size_t Size() const { return items_.size(); }

  T& operator[](std::size_t index) { return items_[index]; }

  const T& operator[](std::size_t index) const { return items_[index]; }

  void Remove(std::size_t index) {
    items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(index));
  }

 private:
  std::vector<T> items_;
};

template <typename T>
double SumEnergy(const Registry<T>& registry) {
  double total = 0.0;
  for (std::size_t i = 0; i < registry.Size(); ++i) {
    total += registry[i]->DailyEnergy();
  }
  return total;
}
