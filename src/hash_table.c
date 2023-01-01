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
    hash += (HT_PRIME * hash + HT_PRIME * key[i] - key[i]) % (HT_SIZE - 1); 
  }
  return hash & (HT_SIZE - 1);
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
void
ht_insert (ht_hash_table *ht, char *key, char *value)
{
  int index;

  index = ht_get_hash (key);
  /* if there is a duplicate key, delete previos one
     and insert new one.  */
  if (ht->items[index] != NULL) {
    ht_del_item (ht->items[index]);
  }
  ht->items[index] = ht_new_item (key, value);
  ++ht->count;
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
      printf("%s: %s\n", ht->items[i]->key, ht->items[i]->value);
    }
  }
}

/* delete an element from hash table. if an element
   is not found then do nothing.  */
void
ht_delete (ht_hash_table *ht, char *key)
{
  int index;
  ht_item *item;

  index = ht_get_hash (key);
  if (strcmp (ht->items[index]->key, key) == 0) {
    ht_del_item (ht->items[index]);
  }
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
test (void)
{
  ht_hash_table *ht = ht_new ();
  ht_insert (ht, "Sam", "+1 2345");
  ht_insert (ht, "Sam", "+2 2345");
  ht_insert (ht, "Jake", "+2 2345");

  char *phone_number = ht_search (ht, "Sams");
  if (phone_number != NULL) {
    printf("Sam's phone number [%s]\n", phone_number);
  }
  else {
    printf("There is no key 'Sams'\n");
  }

  ht_show_hash_table (ht);
  ht_delete_hash_table (ht);
}

int
main (void)
{
  test ();
  return 0;
}
