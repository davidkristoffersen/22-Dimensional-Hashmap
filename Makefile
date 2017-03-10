## Author: Steffen Viken Valvaag <steffenv@cs.uit.no> 
LIST_SRC=linkedlist.c
MAP_SRC=hashmap_multi.c
HASHTABLE_MAIN_SRC=hashtable_main.c common.c $(LIST_SRC) $(MAP_SRC)

HEADERS=common.h list.h map.h

all: hashtable_main

hashtable_main: $(HASHTABLE_MAIN_SRC) $(HEADERS) Makefile
	gcc -g -o $@ $(HASHTABLE_MAIN_SRC)

clean:
	rm -f *~ *.o *.exe hashtable_main
	rm hashtable_main.dSYM
