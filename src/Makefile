
CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG


EXECS = spellcheck

all: $(EXECS) 

doc:
	doxygen


spellcheck: spellcheck.c dnode.c dlist.c lcs.c hash.c
	$(CC) $(CFLAGS) dnode.c dlist.c lcs.c hash.c spellcheck.c -o spellcheck
./clean:
	rm -rf $(EXECS)
