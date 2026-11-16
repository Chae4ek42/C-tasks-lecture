#pragma once

#include <ostream>
#include <string>

constexpr int cMinScore = 1;
constexpr int cMaxScore = 10;
constexpr int cDefaultNoviceScore = 6;

class InventoryItem {
 public:
  InventoryItem(const std::string& inventory_id, const std::string& name);
  virtual ~InventoryItem() = default;

  virtual const std::string& InventoryId() const = 0;
  virtual const std::string& Name() const = 0;
  virtual void Describe(std::ostream& output) const = 0;
  virtual double DailyEnergy() const;
  virtual bool IsTransport() const;
  virtual int Simplicity() const;

 protected:
  std::string inventory_id_;
  std::string name_;
};

class EnergyConsumer {
 public:
  explicit EnergyConsumer(double daily_energy);
  virtual ~EnergyConsumer() = default;

  virtual double DailyEnergy() const = 0;

 protected:
  double daily_energy_;
};

std::ostream& operator<<(std::ostream& output, const InventoryItem& item);
bool operator<(const InventoryItem& first, const InventoryItem& second);
bool operator==(const InventoryItem& first, const InventoryItem& second);
