#include "database.h"
#include <iostream>

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

void release(Entry* target) {
  if (target == NULL) {
    return;
  }

  switch (target->type) {
    case Type::DOUBLE:
      delete (double*) target->value;
      break;
    case Type::STRING:
      delete (std::string*) target->value;
      break;
    case Type::INT:
      delete (int*) target->value;
      break;
    case Type::ARRAY:
      break;
  }

  delete target;
}

void add(Database& database, Entry* entry) {
  Database* useableDatabase = NULL;
  Database* current = &database;
  Database* before = NULL;
  while(current != NULL) {
    if (current->storage == NULL) {
      // 삭제되어 비어있는 경우
      useableDatabase = current;
      break;
    } else {
      if (current->storage->key == entry->key) {
        // 값을 덮어쓸 수 있는 경우
        useableDatabase = current;
        break;
      }
    }

    before = current;
    current = current->next;
  }

  if (useableDatabase == NULL) {
    // 새 데이터베이스 생성
    Database* newDatabase = new Database;
    newDatabase->next = NULL;
    newDatabase->storage = entry;
    before->next = newDatabase;
  } else {
    release(useableDatabase->storage);
    useableDatabase->storage = entry;
  }
}

Entry* get(Database &database, std::string &key) {
  Database* current = &database;
  while (current != NULL) {
    if (
      current->storage != NULL &&
      current->storage->key == key
    ) {
      return current->storage;
    }

    current = current->next;
  }

  return NULL;
}

void remove(Database &database, std::string &key) {
  Database* current = &database;
  while (current != NULL) {
    if (
      current->storage != NULL &&
      current->storage->key == key
    ) {
      release(current->storage);
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
