# CSCI 311 Final Project
Programming Project: Autocorrect

## Team Members
Jim Campbell  
Jack Goldberg  
Tracy Li  
Elsa Perelli 

## Description
This project implements a spellcheck/autocorrect system with C language.
The core algorithm for this spellcheck system is fulfilled by hash table and Longest-Common Subsequence (LCS). 
Finding the words to be checked in the hash table of given word list, if a matched word is found, it is spelled correctly.
Otherwise, the system found the best match in the LCS list of words and correct it.  

## Spelling Errors
This system will look for the LCS with the same length of the input word, and then spread the searching range from this.  
There will be a number of words have the same LCS. 
From our research, people generally spell the first letter of a word correctly. 
Our system will take the LCS word with the same starting letter.  

#### Here are few common spelling errors:  
1. Swapping adjacent letters  
2. Doubling a letter
3. Misusing vowels

## How to run
All the files required to run the program are in the src folder.
Go to our project `csci311_final_project/src`  
Compile the files with command ```make```  
Run the executable ```./spellcheck ```  
You should see a prompt to enter a word.
Then all you have to do is to spell a word, and it will print the best suggestion for a spell error.  
Type "q" to exit.

Example output:  
```
Spell a word: yesterday  
Correctly spelled word  
Spell a word: Swizzerland  
Did you mean: Switzerland
```

