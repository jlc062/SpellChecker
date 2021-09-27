/*
Name: hash.h
Description: hash include file, creates a hash table.
Author: Jim Campbell
*/

#include <string.h>
#define MAX_WORD_LENGTH 16
#define DICT_LENGTH 1804
#define BIG_HASH_VALUE 4294967296

struct hash_entry{
  int value;
  char *string;
};
struct hash_table{
  size_t size;
  int elements;
  struct hash_entry **table;
};

int hash( char *);

void hash_table_insert(struct hash_table *, char*);

int check_hash_table(char *, struct hash_table *word_table);

struct hash_table create_hash_table(size_t size);

void print_hash_table( struct hash_table *word_table);
