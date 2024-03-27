#include <iostream>
#include "database.h"

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
  }

  void _list(Database& db) {
    Database* current = &db;
    while(current != NULL) {
      Entry* data = current->storage;
      if (data != NULL) {
        std::cout << data->key << ": ";
        switch (data->type) {
          case Type::STRING:
            std::cout << (std::string*)data->value << std::endl;
            break;
          case Type::INT:
            std::cout << (int*)data->value << std::endl;
            break;
          case Type::DOUBLE:
            std::cout << (double*)data->value << std::endl;
            break;
          case Type::ARRAY:
            std::cout << "array" << std::endl;
            break;
        }
      }
    }
  }

  void _add(Database& db) {
    Entry data;
    std::string type;
    std::string tmp;

    std::cout << "Key: ";
    std::cin >> data.key;
    std::cout << "Type(int, string, double, array): ";
    std::cin >> type;
    data.type = strToType(type);

    switch (data.type) {
      case Type::STRING:
        std::cin >> tmp;
        data.value = (void*)&tmp;
        break;
      case Type::INT:
        std::cin >> tmp;
        int iTmp = std::stoi(tmp);
        data.value = (void*)&iTmp;
        break;
      case Type::DOUBLE:
        std::cin >> tmp;
        double dTmp = std::stod(tmp);
        data.value = (void*)&dTmp;
        break;
      case Type::ARRAY:
        break;
    }

    add(db, &data);
  }

  void _get(Database& db) {
    std::string key;
    std::cout << "Key: ";
    std::cin >> key;
    Entry entry = get(db, key);

    if (std::is_empty(entry.key)) {
      // 잘못된 키의 경우
      return;
    }

    std::cout << entry.key << ": ";
    switch (entry.type) {
      case Type::STRING:
        std::cout << (std::string*)entry.value << std::endl;
        break;
      case Type::INT:
        std::cout << (int*)entry.value << std::endl;
        break;
      case Type::DOUBLE:
        std::cout << (double*)entry.value << std::endl;
        break;
      case Type::ARRAY:
        std::cout << "TODO ARRAY" << std::endl;
        break;
    }
  }

  void _del(Database& db) {
    std::string key;
    std::cout << "Key: ";
    std::cin >> key;
    remove(db, key);
  }
}

