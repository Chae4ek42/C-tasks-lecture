#include "Inventory.hpp"

#include <cmath>
#include <ostream>

#include "Errors.hpp"

InventoryItem::InventoryItem(const std::string& inventory_id,
                             const std::string& name)
    : inventory_id_(inventory_id), name_(name) {
  if (inventory_id.empty() || name.empty()) {
    throw InvalidCommand("empty id or name");
  }
}

double InventoryItem::DailyEnergy() const { return 0.0; }

bool InventoryItem::IsTransport() const { return false; }

int InventoryItem::Simplicity() const { return 0; }

EnergyConsumer::EnergyConsumer(double daily_energy)
    : daily_energy_(daily_energy) {
  if (!std::isfinite(daily_energy) || daily_energy < 0.0) {
    throw InvalidCommand("energy must be finite and nonnegative");
  }
}

std::ostream& operator<<(std::ostream& output, const InventoryItem& item) {
  item.Describe(output);
  return output;
}

bool operator<(const InventoryItem& first, const InventoryItem& second) {
  return first.InventoryId() < second.InventoryId();
}

bool operator==(const InventoryItem& first, const InventoryItem& second) {
  return first.InventoryId() == second.InventoryId();
}
