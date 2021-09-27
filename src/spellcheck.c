#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
#include "lcs.h"
#include "hash.h"
#include <string.h>


#define MAX_WORD_LENGTH 16
#define WORDLIST_LENGTH 1804  //Amount of words in the file
#define HASH_VALUE 5381

struct dlist *word_array[MAX_WORD_LENGTH]; //Array to hold arrays of words
//change file

struct lcs_word{
  char* word;
  int length;
};


void parseDict(){
	FILE *fd; //File descriptor
	fd = fopen("wordlist.txt", "r"); //Open the dictionary

	char buffer[WORDLIST_LENGTH][MAX_WORD_LENGTH];//Buffer to hold the words in the dictionary

	int i;
	for(i = 0; i < WORDLIST_LENGTH; i++){
		fgets(buffer[i], MAX_WORD_LENGTH, fd); //Iterate by line and fill the buffer
		strtok(buffer[i], "\n"); // strip the newline of the word
	}

	//struct dlist *length_array[MAX_WORD_LENGTH]; //Array of linked lists. One for each word length
	int j;
	for(j = 0; j < MAX_WORD_LENGTH; j++){
		word_array[j] = dlist_create(); //Create a list at each index
	}

	int l;
	for(l = 0; l < WORDLIST_LENGTH; l++){
		dlist_add_back(word_array[strlen(buffer[l]) - 1], (void*) buffer[l]); //Add the word in the buffer to the proper linked list
	}

	fclose(fd);

	// check dict linked list
//	for (int i = 0; i < MAX_WORD_LENGTH; i++) {
//	    struct dnode *n = word_array[i]->front;
//	    while (n != NULL) {
//            printf("%s\n", n->data);
//            n = n->next;
//	    }
//	} // correct!
}

struct hash_table makeHash(){
  int size = HASH_VALUE * WORDLIST_LENGTH;
  struct hash_table word_table = create_hash_table(size);
	FILE *fd; //File descriptor
	fd = fopen("wordlist.txt", "r"); //Open the dictionary

	char buffer[DICT_LENGTH][MAX_WORD_LENGTH];//Buffer to hold the words in the dictionary

	int i;

	for(i = 0; i < WORDLIST_LENGTH; i++){
		fgets( buffer[i], MAX_WORD_LENGTH, fd); //Iterate by line and fill the buffer
    buffer[i][strlen(buffer[i])-1] = '\0';
    //collisions += check_hash_table( buffer[i], &word_table);
    hash_table_insert(&word_table, buffer[i]);
	}
  return word_table;
}

/*
 * Function for checking work. Prints nodes in a linked list
 */
void traverse_forward(struct dlist *l) {
    char *str;
    fflush(stdout);
    for (str = (char*) dlist_iter_begin(l); str != NULL;
        str = (char*) dlist_iter_next(l))   {
       // printf("WORD: %s\n", str);
    }
}

struct lcs_word* lcs_set(struct dlist *l, char* input){
	char *str;
	int lcs_return;
	int max_lcs = 0;
	char max_word[100];

    for (str = (char*) dlist_iter_begin(l); str != NULL;
       str = (char*) dlist_iter_next(l)) {
//        printf("str: %s\n", str);
        lcs_return = lcs(input, str, strlen(input), strlen(str));
 //       printf("str: %s %d\n", str, lcs_return);
        if (lcs_return == strlen(input)) {
   //         printf("Found word\n");
            struct lcs_word *return_word;
            return_word = malloc(sizeof(struct lcs_word));
            return_word->word = malloc(sizeof(char[100]));
            strcpy(return_word->word, str);
            return_word->length = lcs_return;
            return return_word;
        }

        //printf("lcs return: %d\n", lcs_return);
        if (lcs_return == max_lcs && str[0] == input[0] &&
            max_word[0] != input[0]) {    //Equal LCS, but the new word shares the first letter with input
            max_lcs = lcs_return;
            strcpy(max_word, str);
     //       printf("str: %s, max_word: %s\n", str, max_word);
        } else if (lcs_return > max_lcs) { //new lcs is greater than current lcs
            max_lcs = lcs_return;
            strcpy(max_word, str);
       //     printf("str: %s, max_word: %s\n", str, max_word);
        }

    }
//	printf("Best match: %s\n", max_word);
	struct lcs_word *return_word;
	return_word =  malloc(sizeof(struct lcs_word));

	return_word->word = malloc(sizeof(char[100]));
	strcpy(return_word->word, max_word);
	return_word->length = max_lcs;

	//printf("return word: %s %d\n", return_word->word, lcs_return);
	return return_word;
}


int main(){

	parseDict(); //Parse the dictionary
  struct hash_table word_table = makeHash();

	int k;

	//get user input
	while(true){
		struct lcs_word *best_word;
		best_word = malloc(sizeof(struct lcs_word));
		best_word->length = 0;
		struct lcs_word *temp_word;
		temp_word = malloc(sizeof(struct lcs_word));

		char input[100];
		printf("Spell a word: ");
		scanf("%s", input);
    if (input[0] == 'q' && strlen(input) == 1){
      exit(0);
    }
    if (check_hash_table(input, &word_table) == 1){
      printf("Correctly spelled Word\n");
      continue;
    }else{
		//Calculate bounds for search

		int lower_bound = (int) ((double) strlen(input) * (double) (.75));
		int upper_bound = (int) ((double) strlen(input) * (double) (1.25));
		if(upper_bound > 14){
			upper_bound = 14;
		}
	//	printf("lower bound: %d, upper bound: %d", lower_bound, upper_bound);
		for(k = lower_bound; k <= upper_bound; k++){
		    traverse_forward(word_array[k]);
			//Loop and check
			temp_word = lcs_set(word_array[k], input); //Check input against words of length k
//			printf("temp: %s %d\n", temp_word->word, temp_word->length);
			if(temp_word->length > best_word->length){
	//			printf("inside\n");
				best_word->word =  temp_word->word;
				best_word->length = temp_word->length;
			}
//			printf("best: %s\n", best_word->word);
		}
		printf("Did you mean %s\n", best_word->word);
		free(best_word);
		free(temp_word);
		}
	}

	return 0;
}
