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
  Database next;
  init(next);
  database.storage = entry;
  database.next = &next;
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

  return {};
}

void remove(Database &database, std::string &key) {
  Database* current = &database;
  while (current != NULL) {
    if (
      current->storage != NULL &&
      current->storage->key == key
    ) {
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