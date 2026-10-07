#include <cctype>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

constexpr int cRows = 5;
constexpr int cColumns = 10;

void Clear(char board[cRows][cColumns + 1]) {
  for (int y = 0; y < cRows; ++y) {
    for (int x = 0; x < cColumns; ++x) {
      board[y][x] = ' ';
    }
    board[y][cColumns] = '\0';
  }
}

bool Put(char board[cRows][cColumns + 1], int x, int y, char symbol) {
  if (x < 0 || x >= cColumns || y < 0 || y >= cRows) {
    return false;
  }
  board[y][x] = symbol;
  return true;
}

bool Text(char board[cRows][cColumns + 1], int x, int y, const char* word,
          int word_length) {
  if (x < 0 || x >= cColumns || y < 0 || y >= cRows ||
      word_length > cColumns - x) {
    return false;
  }

  for (int i = 0; i < word_length; ++i) {
    board[y][x + i] = word[i];
  }
  return true;
}

void Print(const char board[cRows][cColumns + 1]) {
  for (int y = 0; y < cRows; ++y) {
    std::cout << board[y] << '\n';
  }
}

int main() {
  char board[cRows][cColumns + 1];
  Clear(board);

  char command[sizeof("clear")];
  while (std::cin >> std::setw(sizeof(command)) >> command) {
    if (std::strcmp(command, "quit") == 0) {
      break;
    } else if (std::strcmp(command, "clear") == 0) {
      Clear(board);
    } else if (std::strcmp(command, "print") == 0) {
      Print(board);
    } else if (std::strcmp(command, "put") == 0) {
      int x;
      int y;
      char symbol;
      if (!(std::cin >> x >> y >> symbol) || !Put(board, x, y, symbol)) {
        std::cout << "error\n";
      }
    } else if (std::strcmp(command, "text") == 0) {
      int x;
      int y;
      char word[cColumns + 1];
      if (!(std::cin >> x >> y)) {
        std::cout << "error\n";
        return 1;
      }
      if (!(std::cin >> std::setw(sizeof(word)) >> word)) {
        std::cout << "error\n";
        return 1;
      }

      const int cWordLength = static_cast<int>(std::strlen(word));
      const int cNextCharacter = std::cin.peek();
      const bool cWordWasTruncated =
          cNextCharacter != EOF &&
          !std::isspace(static_cast<unsigned char>(cNextCharacter));

      if (cWordWasTruncated || !Text(board, x, y, word, cWordLength)) {
        std::cout << "error\n";
      }
    } else {
      std::cout << "error\n";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  return 0;
}
