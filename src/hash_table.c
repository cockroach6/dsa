#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

#define HT_SIZE  20
#define HT_PRIME 2069


static int
ht_get_hash (char *key)
{
  int hash = 0;

  for (int i = 0; i < strlen (key); ++i) {
    hash += (HT_PRIME * hash + HT_PRIME * key[i] - key[i]) % HT_SIZE;
  }
  return hash % HT_SIZE;
}

static ht_item
*ht_new_item (char *key, char *value)
{
  ht_item *item = malloc (sizeof (ht_item));
  if (item == NULL) {
    fprintf(stderr, "err: malloc failed for ht_new_item()\n");
    return NULL;
  }
  item->key = strdup (key);
  item->value = strdup (value);
  return item;
}

static void
ht_del_item (ht_item *item)
{
  free (item->key);
  free (item->value);
  free (item);
}

ht_hash_table
*ht_new (void)
{
  ht_hash_table *ht = calloc (1, sizeof (ht_hash_table));
  if (ht == NULL) {
    fprintf(stderr, "err: malloc for ht_new() failed\n");
    return NULL;
  }
  ht->count = 0;
  ht->size = HT_SIZE;
  ht->items = calloc (ht->size, sizeof (ht_item*));
  if (ht->items == NULL) {
    if (ht != NULL) {
      free (ht);
    }
    return NULL;
  }
  return ht;
}


/* TODO: handle collisions */
/* hash table is meant to increase/ decrise
   its size so there alwals will be space for
   new item.  */
int
ht_insert (ht_hash_table *ht, char *key, char *value)
{
  int index;

  if (ht->count + 1 >= ht->size) {
    fprintf(stderr, "err: hash table is full\n");
    return 1;
  }

  /* if index is not free look for next free space.  */
  index = ht_get_hash (key);
  do {
    index = index % HT_SIZE;
    ++index;
  } while (ht->items[index] != NULL);

  ht->items[index] = ht_new_item (key, value);
  ++ht->count;
  return 0;
}

char
*ht_search (ht_hash_table *ht, char *key)
{
  int index;

  index = ht_get_hash (key);
  if (ht->items[index] != NULL) {
    if (strcmp (ht->items[index]->key, key) == 0) {
      return ht->items[index]->value;
    }
  }
  return NULL;
}

void
ht_show_hash_table (ht_hash_table *ht)
{
  for (int i = 0; i < ht->size; ++i) {
    if (ht->items[i] != NULL) {
      printf("idx=%d: %s: %s\n", i, ht->items[i]->key, ht->items[i]->value);
    }
  }
}

/* delete an element from hash table. if an element
   is not found then do nothing.  */
void
ht_delete (ht_hash_table *ht, char *key)
{
  int index;


  /* if index is not free look for next free space.  */
  index = ht_get_hash (key);
  while (ht->items[index] == NULL) {
    ++index;
    index %= HT_SIZE;    
  }

  ht_del_item (ht->items[index]);
  ht->items[index] = NULL;
  --ht->count;
}

void ht_delete_hash_table (ht_hash_table *ht)
{
  ht_item *item;

  if (ht == NULL) {
    return ;
  }
  for (int i = 0; i < ht->size; ++i) {
    item = ht->items[i];
    if (item != NULL) {
      ht_del_item (ht->items[i]);
    }
  }
  free (ht->items);
  free (ht);
}


void
hash_table_test (void)
{
  ht_hash_table *ht = ht_new ();

  printf("Hash Table\n");
  ht_insert (ht, "Sam", "+1 2345");
  ht_insert (ht, "Sam", "+2 2345");
  ht_insert (ht, "Sam", "+2 2345");
  ht_insert (ht, "Sam", "+2 2345");
  ht_insert (ht, "Sam", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");
  ht_delete (ht, "Jake");

  ht_show_hash_table (ht);
  ht_delete_hash_table (ht);
}
