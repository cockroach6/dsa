#ifndef ROACH_HASH_TABLE_H
#define ROACH_HASH_TABLE_H

#include <stdio.h>

typedef struct {
  char *key;
  char *value;
} ht_item;

typedef struct {
  size_t count;
  size_t size;
  ht_item **items;
} ht_hash_table;

ht_hash_table *ht_new (void);
int ht_insert (ht_hash_table *ht, char *key, char *value);
char *ht_search (ht_hash_table *ht, char *key);
void ht_show_hash_table (ht_hash_table *ht);
void ht_delete (ht_hash_table *ht, char *key);
void ht_delete_hash_table (ht_hash_table *ht);

void hash_table_test (void);
#endif
