#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "database.h"

namespace Parser {
  Type strToType(std::string& str);

  void _addArray(Array* root);

  void _listArray(Array* array);

  void _list(Database& db);

  void _add(Database& db);

  void _get(Database& db);

  void _del(Database& db);

  void _delAll(Database& db);
}

#endif // PARSER_H
