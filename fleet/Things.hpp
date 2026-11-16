#pragma once

#include "Inventory.hpp"

class Helmet : public InventoryItem {
 public:
  Helmet(const std::string& inventory_id, const std::string& name);

  const std::string& InventoryId() const override;
  const std::string& Name() const override;
  void Describe(std::ostream& output) const override;
};

class Dock : public InventoryItem, public EnergyConsumer {
 public:
  Dock(const std::string& inventory_id, const std::string& name,
       double daily_energy);

  const std::string& InventoryId() const override;
  const std::string& Name() const override;
  void Describe(std::ostream& output) const override;
  double DailyEnergy() const override;
};
