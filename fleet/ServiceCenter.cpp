#include "ServiceCenter.hpp"

#include <cctype>
#include <string>

#include "Errors.hpp"

void ServiceCenter::Inspect(const InventoryItem& item) {
  if (!item.IsTransport()) {
    return;
  }

  std::string name = item.Name();
  for (char& symbol : name) {
    symbol =
        static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
  }

  if (name.find("broken") != std::string::npos) {
    throw InspectionRejected();
  }
}
