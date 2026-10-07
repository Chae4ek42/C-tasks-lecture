#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

using Operation = void (*)(int&, int);

void Deposit(int& balance, int amount) {
  if (amount <= 0) {
    std::cout << "error\n";
    return;
  }
  balance += amount;
}

void Withdraw(int& balance, int amount) {
  if (amount <= 0 || amount > balance) {
    std::cout << "error\n";
    return;
  }
  balance -= amount;
}

void PrintBalance(int& balance, int) {
  std::cout << balance << '\n';
}

void Reset(int& balance, int) {
  balance = 0;
}

void Increment(int& balance, int) {
  ++balance;
}

struct Command {
  const char* name;
  Operation operation;
  bool needs_amount;
};

int main() {
  const Command cCommands[] = {
      {"deposit", Deposit, true}, {"withdraw", Withdraw, true},
      {"balance", PrintBalance, false}, {"reset", Reset, false},
      {"inc", Increment, false}};
  const int cCommandCount = sizeof(cCommands) / sizeof(cCommands[0]);

  int balance = 0;
  char command[sizeof("withdraw")];

  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    const Command* selected_command = nullptr;
    for (int i = 0; i < cCommandCount; ++i) {
      if (std::strcmp(command, cCommands[i].name) == 0) {
        selected_command = &cCommands[i];
        break;
      }
    }

    if (selected_command == nullptr) {
      std::cout << "error\n";
    } else {
      int amount = 0;
      if (selected_command->needs_amount && !(std::cin >> amount)) {
        std::cout << "error\n";
        return 1;
      }
      selected_command->operation(balance, amount);
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
