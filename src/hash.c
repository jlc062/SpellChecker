/*
Name: hash.c
Date: 11/18/20
Description:
A c program that takes a string and produces a hashhvalue
for the string.
Author: Jim Campbell
Sources: 
www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
https://stackoverflow.com/questions/7666509/hash-function-for-string

*/

#define MAX_STRING 16
#define MAX_WORD_LENGTH 16
#define DICT_LENGTH 1804
#define BIG_HASH_VALUE 4294967296

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

int hash( char *string){
  unsigned int hash_val = 5381;
  int c;
  while ((c = *string++))
    hash_val = ((hash_val<< 5) + hash_val) + c;
  return hash_val;
}
  /*
  const int ret_size = 32;
  size_t ret = 0x555555;
  const int per_char = 7;
  while (*string){
    ret ^= *string++;
    ret = ((ret << per_char) | (ret >> (ret_size - per_char)));
  }
  return ret;
  */

void hash_table_insert(struct hash_table *word_table, char *string ){
  struct hash_entry * entry;
  int hash_value;

  entry = malloc(sizeof(*entry));

  hash_value = hash(string);
  hash_value =  hash_value % word_table->size;
  //printf("%d\n", hash_value);
  entry->value = hash_value;
  entry->string = malloc(sizeof(char *));
  entry->string = string;
  word_table->table[hash_value] = entry;
  word_table->elements++;

}

struct hash_table create_hash_table(size_t size){
  struct hash_table *word_table;
  word_table = (struct hash_table *) malloc(sizeof(word_table));
  word_table->size = size;
  word_table->elements = 0;
  word_table->table = malloc(sizeof(struct hash_entry *) * size);
  int i;
  for (i = 0; i < size; i++){
    word_table->table[i] = 0;
  }
  return *word_table;
}

int check_hash_table( char *string, struct hash_table *word_table){
  int hash_value = hash(string);
  hash_value = hash_value % word_table->size;
  if ( word_table->table[hash_value] == 0) {
    return 0;
  } else {
    return 1;
  }
}
void print_hash_table( struct hash_table *word_table){
  int i;
  for (i =0; i < word_table->size; i++){
    if (word_table->table[i] == 0){
      continue;
    } else {
      printf("Value: %d\n", i);
      printf("Word: %s\n", word_table->table[i]->string);
    }
  }

}
/*
int main(int argc, char const *argv[]) {
   //Amount of words in the file
  int size = 5381 * 1804;
  struct hash_table word_table= create_hash_table(size);
	FILE *fd; //File descriptor
	fd = fopen("wordlist.txt", "r"); //Open the dictionary

	char buffer[DICT_LENGTH][MAX_WORD_LENGTH];//Buffer to hold the words in the dictionary

	int i;

	for(i = 0; i < 1804; i++){
		fgets( buffer[i], MAX_WORD_LENGTH, fd); //Iterate by line and fill the buffer
    buffer[i][strlen(buffer[i])-1] = '\0';
    collisions += check_hash_table( buffer[i], &word_table);
    hash_table_insert(&word_table, buffer[i]);
	}
  if (check_hash_table("Jupiter", &word_table) == 1){
    printf("Got it\n");
  }

  //print_hash_table(&word_table);
  return 0;
}
*/
