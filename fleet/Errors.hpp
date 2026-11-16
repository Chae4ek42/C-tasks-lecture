#pragma once

#include <exception>
#include <string>

class FleetError : public std::exception {
 public:
  explicit FleetError(const std::string& message) : message_(message) {}

  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class InspectionRejected : public FleetError {
 public:
  InspectionRejected() : FleetError("inspection rejected") {}
};

class InvalidCommand : public FleetError {
 public:
  explicit InvalidCommand(const std::string& message) : FleetError(message) {}
};
