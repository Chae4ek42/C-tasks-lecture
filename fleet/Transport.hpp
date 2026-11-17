#pragma once

#include "Inventory.hpp"

class Transport : public InventoryItem {
 public:
  Transport(const std::string& inventory_id, const std::string& name,
            int simplicity);

  const std::string& InventoryId() const override;
  const std::string& Name() const override;
  void Describe(std::ostream& output) const override;
  double DailyEnergy() const override = 0;
  bool IsTransport() const override;
  int Simplicity() const override;

 private:
  int simplicity_;
};

class Bike : public Transport {
 public:
  Bike(const std::string& inventory_id, const std::string& name,
       int simplicity);

  double DailyEnergy() const override;
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(const std::string& inventory_id, const std::string& name,
                  double daily_energy, int simplicity);

  double DailyEnergy() const override;
};

class ElectricBike : public Transport, public EnergyConsumer {
 public:
  ElectricBike(const std::string& inventory_id, const std::string& name,
               double daily_energy, int simplicity);

  double DailyEnergy() const override;
};

class Helicopter : public Transport, public EnergyConsumer {
 public:
  Helicopter(const std::string& inventory_id, const std::string& name,
             double daily_energy);

  double DailyEnergy() const override;
};
