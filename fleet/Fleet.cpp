#include "Fleet.hpp"

#include <algorithm>
#include <cstdlib>
#include <ostream>
#include <utility>
#include <vector>

#include "Errors.hpp"
#include "ServiceCenter.hpp"

void Fleet::Add(std::unique_ptr<InventoryItem> item) {
  for (std::size_t i = 0; i < items_.Size(); ++i) {
    if (*items_[i] == *item) {
      throw InvalidCommand("duplicate id");
    }
  }

  ServiceCenter::Inspect(*item);
  items_.Add(std::shared_ptr<InventoryItem>(std::move(item)));
}

void Fleet::Remove(const std::string& inventory_id) {
  items_.Remove(FindIndex(inventory_id));
}

std::size_t Fleet::Count() const { return items_.Size(); }

double Fleet::TotalEnergy() const { return SumEnergy(items_); }

void Fleet::PrintAll(std::ostream& output) const {
  std::vector<std::shared_ptr<InventoryItem>> sorted;
  for (std::size_t i = 0; i < items_.Size(); ++i) {
    sorted.push_back(items_[i]);
  }

  std::sort(sorted.begin(), sorted.end(),
            [](const std::shared_ptr<InventoryItem>& first,
               const std::shared_ptr<InventoryItem>& second) {
              return *first < *second;
            });

  for (const auto& item : sorted) {
    output << *item << '\n';
  }
}

void Fleet::PrintNovice(std::ostream& output, int minimum_score) const {
  if (minimum_score < cMinScore || minimum_score > cMaxScore) {
    throw InvalidCommand("score must be between 1 and 10");
  }

  for (std::size_t i = 0; i < items_.Size(); ++i) {
    if (items_[i]->IsTransport() && items_[i]->Simplicity() >= minimum_score) {
      output << *items_[i] << '\n';
    }
  }
}

void Fleet::PrintClosest(std::ostream& output, int score) const {
  if (score < cMinScore || score > cMaxScore) {
    throw InvalidCommand("score must be between 1 and 10");
  }

  std::shared_ptr<InventoryItem> closest;
  int best_distance = cMaxScore;
  for (std::size_t i = 0; i < items_.Size(); ++i) {
    if (!items_[i]->IsTransport()) {
      continue;
    }

    int distance = std::abs(items_[i]->Simplicity() - score);
    if (!closest || distance < best_distance ||
        (distance == best_distance && *items_[i] < *closest)) {
      closest = items_[i];
      best_distance = distance;
    }
  }

  if (closest) {
    output << *closest << '\n';
  } else {
    output << "no transport\n";
  }
}

void Fleet::Focus(const std::string& inventory_id) {
  focus_ = items_[FindIndex(inventory_id)];
}

void Fleet::ShowFocus(std::ostream& output) const {
  if (auto selected = focus_.lock()) {
    output << *selected << '\n';
  } else {
    output << "removed / expired\n";
  }
}

std::size_t Fleet::FindIndex(const std::string& inventory_id) const {
  for (std::size_t i = 0; i < items_.Size(); ++i) {
    if (items_[i]->InventoryId() == inventory_id) {
      return i;
    }
  }
  throw InvalidCommand("id not found");
}
