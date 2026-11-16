#include "Things.hpp"

#include <ostream>

Helmet::Helmet(const std::string& inventory_id, const std::string& name)
    : InventoryItem(inventory_id, name) {}

const std::string& Helmet::InventoryId() const { return inventory_id_; }

const std::string& Helmet::Name() const { return name_; }

void Helmet::Describe(std::ostream& output) const {
  output << InventoryId() << ' ' << Name();
}

Dock::Dock(const std::string& inventory_id, const std::string& name,
           double daily_energy)
    : InventoryItem(inventory_id, name), EnergyConsumer(daily_energy) {}

const std::string& Dock::InventoryId() const { return inventory_id_; }

const std::string& Dock::Name() const { return name_; }

void Dock::Describe(std::ostream& output) const {
  output << InventoryId() << ' ' << Name();
}

double Dock::DailyEnergy() const { return daily_energy_; }
