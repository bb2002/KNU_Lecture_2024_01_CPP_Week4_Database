#include <iostream>
#include "database.h"
#include "parser.cpp"

int main() {
  std::cout << "Welcome to BallbotDB Monitor" << std::endl;
  Database db;
  init(db);

  std::string command;
  while (true) {
    std::cout << "command (list, add, get, del, exit) ";
    std::cin >> command;

    if (command == "list") {
      Parser::_list(db);
    }

    if (command == "add") {
      Parser::_add(db);
    }

    if (command == "get") {
      Parser::_get(db);
    }

    if (command == "del") {
      Parser::_del(db);
    }

    if (command == "exit") {
      std::cout << "Goodbye" << std::endl;
      break;
    }
  }
}