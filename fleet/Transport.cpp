#include "Transport.hpp"

#include <ostream>

#include "Errors.hpp"

Transport::Transport(const std::string& inventory_id, const std::string& name,
                     int simplicity)
    : InventoryItem(inventory_id, name), simplicity_(simplicity) {
  if (simplicity < cMinScore || simplicity > cMaxScore) {
    throw InvalidCommand("score must be between 1 and 10");
  }
}

const std::string& Transport::InventoryId() const { return inventory_id_; }

const std::string& Transport::Name() const { return name_; }

void Transport::Describe(std::ostream& output) const {
  output << InventoryId() << ' ' << Name();
}

bool Transport::IsTransport() const { return true; }

int Transport::Simplicity() const { return simplicity_; }

Bike::Bike(const std::string& inventory_id, const std::string& name,
           int simplicity)
    : Transport(inventory_id, name, simplicity) {}

double Bike::DailyEnergy() const { return 0.0; }

ElectricScooter::ElectricScooter(const std::string& inventory_id,
                                 const std::string& name, double daily_energy,
                                 int simplicity)
    : Transport(inventory_id, name, simplicity), EnergyConsumer(daily_energy) {}

double ElectricScooter::DailyEnergy() const { return daily_energy_; }

ElectricBike::ElectricBike(const std::string& inventory_id,
                           const std::string& name, double daily_energy,
                           int simplicity)
    : Transport(inventory_id, name, simplicity), EnergyConsumer(daily_energy) {}

double ElectricBike::DailyEnergy() const { return daily_energy_; }

Helicopter::Helicopter(const std::string& inventory_id, const std::string& name,
                       double daily_energy)
    : Transport(inventory_id, name, 3), EnergyConsumer(daily_energy) {}

double Helicopter::DailyEnergy() const { return daily_energy_; }
