#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Fleet.hpp"
#include "Things.hpp"
#include "Transport.hpp"

void CheckEnd(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw InvalidCommand("unexpected argument");
  }
}

std::unique_ptr<InventoryItem> ReadItem(std::istringstream& input) {
  std::string type;
  std::string inventory_id;
  std::string name;
  if (!(input >> type >> inventory_id >> name)) {
    throw InvalidCommand("expected type, id and name");
  }

  std::unique_ptr<InventoryItem> item;
  if (type == "scooter" || type == "ebike") {
    double energy = 0.0;
    int score = 0;
    if (!(input >> energy >> score)) {
      throw InvalidCommand("expected energy and score");
    }
    if (type == "scooter") {
      item =
          std::make_unique<ElectricScooter>(inventory_id, name, energy, score);
    } else {
      item = std::make_unique<ElectricBike>(inventory_id, name, energy, score);
    }
  } else if (type == "bike") {
    int score = 0;
    if (!(input >> score)) {
      throw InvalidCommand("expected score");
    }
    item = std::make_unique<Bike>(inventory_id, name, score);
  } else if (type == "helmet") {
    item = std::make_unique<Helmet>(inventory_id, name);
  } else if (type == "dock") {
    double energy = 0.0;
    if (!(input >> energy)) {
      throw InvalidCommand("expected energy");
    }
    item = std::make_unique<Dock>(inventory_id, name, energy);
  } else {
    throw InvalidCommand("unknown item type");
  }

  CheckEnd(input);
  return item;
}

bool ExecuteCommand(const std::string& line, Fleet& fleet) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }

  if (command == "add") {
    fleet.Add(ReadItem(input));
  } else if (command == "novice") {
    int minimum_score = cDefaultNoviceScore;
    input >> std::ws;
    if (!input.eof() && !(input >> minimum_score)) {
      throw InvalidCommand("expected score");
    }
    CheckEnd(input);
    fleet.PrintNovice(std::cout, minimum_score);
  } else if (command == "focus" || command == "remove") {
    std::string inventory_id;
    if (!(input >> inventory_id)) {
      throw InvalidCommand("expected id");
    }
    CheckEnd(input);
    if (command == "focus") {
      fleet.Focus(inventory_id);
    } else {
      fleet.Remove(inventory_id);
    }
  } else {
    CheckEnd(input);
    if (command == "list") {
      fleet.PrintAll(std::cout);
    } else if (command == "count") {
      std::cout << fleet.Count() << '\n';
    } else if (command == "energy") {
      std::cout << std::fixed << std::setprecision(1) << fleet.TotalEnergy()
                << '\n';
    } else if (command == "show_focus") {
      fleet.ShowFocus(std::cout);
    } else if (command == "quit") {
      return false;
    } else {
      throw InvalidCommand("unknown command");
    }
  }
  return true;
}

int main() {
  Fleet fleet;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, fleet)) {
        break;
      }
    } catch (const FleetError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
  return 0;
}
