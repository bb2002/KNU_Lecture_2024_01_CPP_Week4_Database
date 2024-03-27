#include <iostream>
#include "database.h"
#include "parser.h"

namespace Parser {
  Type strToType(std::string& str) {
    if (str == "int") {
      return Type::INT;
    }
    if (str == "double") {
      return Type::DOUBLE;
    }
    if (str == "string") {
      return Type::STRING;
    }
    if (str == "array") {
      return Type::ARRAY;
    }

    return Type::INT;
  }

  void _list(Database& db) {
    Database* current = &db;
    while(current != NULL) {
      Entry* data = current->storage;
      if (data != NULL) {
        std::cout << data->key << ": ";
        switch (data->type) {
          case Type::STRING:
            std::cout << *(std::string*)data->value << std::endl;
            break;
          case Type::INT:
            std::cout << *(int*)data->value << std::endl;
            break;
          case Type::DOUBLE:
            std::cout << *(double*)data->value << std::endl;
            break;
          case Type::ARRAY:
            std::cout << "array" << std::endl;
            break;
        }
      }
      current = current->next;
    }
  }

  void _add(Database& db) {
    Entry* data = new Entry;
    std::string type;

    std::cout << "Key: ";
    std::cin >> (*data).key;
    std::cout << "Type(int, string, double, array): ";
    std::cin >> type;
    std::cout << "Value: ";

    if (type == "string") {
      data->type = Type::STRING;
      data->value = new std::string;
      std::getchar();
      std::getline(std::cin, *(std::string*)data->value);
    }

    if (type == "int") {
      std::string tmp;
      data->type = Type::INT;
      data->value = new int;
      std::cin >> tmp;
      *(int*)data->value = std::stoi(tmp);
    }

    if (type == "double") {
      std::string tmp;
      data->type = Type::DOUBLE;
      data->value = new double;
      std::cin >> tmp;
      *(double*)data->value = std::stod(tmp);
    }

    add(db, data);
  }

  void _get(Database& db) {
    std::string key;
    std::cout << "Key: ";
    std::cin >> key;
    Entry entry = get(db, key);

    if (entry.key == "") {
      // 잘못된 키의 경우
      return;
    }

    std::cout << entry.key << ": ";
    switch (entry.type) {
      case Type::STRING:
        std::cout << *(std::string*)entry.value << std::endl;
        break;
      case Type::INT:
        std::cout << *(int*)entry.value << std::endl;
        break;
      case Type::DOUBLE:
        std::cout << *(double*)entry.value << std::endl;
        break;
      case Type::ARRAY:
        std::cout << "TODO ARRAY" << std::endl;
        break;
    }

    std::cout << std::endl;
  }

  void _del(Database& db) {
    std::string key;
    std::cout << "Key: ";
    std::cin >> key;
    remove(db, key);
  }
}

