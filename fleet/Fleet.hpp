#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

#include "Inventory.hpp"
#include "Registry.hpp"

class Fleet {
 public:
  void Add(std::unique_ptr<InventoryItem> item);
  void Remove(const std::string& inventory_id);
  std::size_t Count() const;
  double TotalEnergy() const;
  void PrintAll(std::ostream& output) const;
  void PrintNovice(std::ostream& output, int minimum_score) const;
  void PrintClosest(std::ostream& output, int score) const;
  void Focus(const std::string& inventory_id);
  void ShowFocus(std::ostream& output) const;

 private:
  std::size_t FindIndex(const std::string& inventory_id) const;

  Registry<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> focus_;
};
