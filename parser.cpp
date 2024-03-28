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

  void _addArray(Array* root) {
    std::string type;
    int size;
    std::cout << "type (int, double, string, array):";
    std::cin >> type;
    std::cout << "size: ";
    std::cin >> size;

    if (type == "string") {
      auto cont = new std::string[size];
      root->items = cont;
      root->size = size;
      root->type = Type::STRING;

      for (int i = 0; i < size; ++i) {
        std::cout << "item[" << i << "]: ";
        std::cin >> cont[i];
      }
    }
    if (type == "int") {
      auto cont = new int[size];
      root->items = cont;
      root->size = size;
      root->type = Type::INT;

      for (int i = 0; i < size; ++i) {
        std::cout << "item[" << i << "]: ";
        std::cin >> cont[i];
      }
    }
    if (type == "double") {
      auto cont = new double[size];
      root->items = cont;
      root->size = size;
      root->type = Type::DOUBLE;

      for (int i = 0; i < size; ++i) {
        std::cout << "item[" << i << "]: ";
        std::cin >> cont[i];
      }
    }
    if (type == "array") {
      auto cont = new Array[size];
      root->items = cont;
      root->size = size;
      root->type = Type::ARRAY;

      for (int i = 0; i < size; ++i) {
        _addArray(&cont[i]);
      }
    }
  }

  void _listArray(Array* array) {
    std::cout << "[";

    for (int i = 0; i < array->size; ++i) {
      switch (array->type) {
        case Type::INT:
          std::cout << ((int*)array->items)[i];
          break;
        case Type::STRING:
          std::cout << ((std::string*)array->items)[i];
          break;
        case Type::DOUBLE:
          std::cout << ((double*)array->items)[i];
          break;
        case Type::ARRAY:
          _listArray(&((Array*)array->items)[i]);
          break;
      }

      if (i != array->size - 1) {
        std::cout << ", ";
      }
    }
    std::cout << "]";
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
            auto cont = (Array*) data->value;
            _listArray(cont);
            std::cout << std::endl;
            break;
        }
      }
      current = current->next;
    }
  }

  void _add(Database& db) {
    Entry* data = new Entry;
    std::string type;

    std::cout << "key: ";
    std::cin >> (*data).key;
    std::cout << "type (int, double, string, array):";
    std::cin >> type;
    std::cout << "value: ";

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

    if (type == "array") {
      Array* array = new Array;
      _addArray(array);
      data->type = Type::ARRAY;
      data->value = array;
    }

    add(db, data);
  }

  void _get(Database& db) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;
    Entry* entry = get(db, key);

    if (entry == NULL) {
      return;
    }

    std::cout << entry->key << ": ";
    switch (entry->type) {
      case Type::STRING:
        std::cout << *(std::string*)entry->value << std::endl;
        break;
      case Type::INT:
        std::cout << *(int*)entry->value << std::endl;
        break;
      case Type::DOUBLE:
        std::cout << *(double*)entry->value << std::endl;
        break;
      case Type::ARRAY:
        _listArray((Array*)entry->value);
        std::cout << std::endl;
        break;
    }

    std::cout << std::endl;
  }

  void _del(Database& db) {
    std::string key;
    std::cout << "key: ";
    std::cin >> key;
    remove(db, key);
  }
}

