#include "database.h"

Entry *create(Type type, std::string key, void *value) {
  Entry* data = new Entry;
  data->type = type;
  data->key = key;
  data->value = value;
  return data;
}

void init(Database& database) {
  database.storage = NULL;
  database.next = NULL;
}

void add(Database& database, Entry* entry) {
  Database* newDatabase = new Database;
  Database* next = &database;
  newDatabase->next = NULL;
  newDatabase->storage = entry;
  while (next->next != NULL) {
    next = next->next;
  }

  next->next = newDatabase;
}

Entry get(Database &database, std::string &key) {
  Database* current = &database;
  while (current != NULL) {
    if (
      current->storage != NULL &&
      current->storage->key == key
    ) {
      return *(current->storage);
    }

    current = current->next;
  }

  Entry err;
  err.key = "";
  return err;
}

void remove(Database &database, std::string &key) {
  Database* current = &database;
  while (current != NULL) {
    if (
      current->storage != NULL &&
      current->storage->key == key
    ) {
      switch (current->storage->type) {
        case Type::DOUBLE:
          delete (double*) current->storage->value;
          break;
        case Type::STRING:
          delete (std::string*) current->storage->value;
          break;
        case Type::INT:
          delete (int*) current->storage->value;
          break;
        case Type::ARRAY:
          break;
      }

      delete current->storage;
      current->storage = NULL;
    }

    current = current->next;
  }
}

void destroy(Database& database) {
  Database* current = &database;
  while(current != NULL) {
    if (current->storage != NULL) {
      delete current->storage;
    }

    current = current->next;
    delete current;
  }
}