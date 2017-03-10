/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include "common.h"
#include "list.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>

struct word {
	char *word;
	int freq;
};

word_t *create_word(char *word, int freq) {
	word_t *tmpword = malloc(sizeof(word_t));
	tmpword->word = word;
	tmpword->freq = freq;
	return tmpword;
}

void *new_int(int a) {
	void *new_int = malloc(sizeof(int));
	*(int*)new_int = a;
	return new_int;
}

int main(int argc, char **argv) {
	printf("\n");	
	FILE *f;
	f = fopen(argv[1], "r");
	if (f == NULL) {
		perror("fopen");
		fatal_error("fopen() failed");
	}
	list_t *init_wordlist = list_create(compare_strings);
	tokenize_file(f, init_wordlist);
	list_t *wordlist_nodup = list_create(compare_strings);

	map_t *map = map_create(compare_strings, hash_string);

	void *tmp_word;
	void *tmp_val_p;
	int tmp_val;
	while (list_size(init_wordlist) > 0) {
		tmp_word = list_poplast(init_wordlist);
		if (map_haskey(map, tmp_word) == 1) {
			tmp_val_p = map_get(map, tmp_word);
			int tmp_val = *(int*)tmp_val_p;
			map_put(map, tmp_word, new_int(tmp_val + 1));
		}
		else {
			map_put(map, tmp_word, new_int(1));
			list_addlast(wordlist_nodup, tmp_word);
		}
	}

	// Populating list with words and freqs
	list_t *wordlist = list_create(freq_compare);
	char *tmpword;
	while (list_size(wordlist_nodup) > 0) {
		tmpword = list_poplast(wordlist_nodup);

		int a = *(int*)map_get(map, tmpword);
		word_t *word = create_word(tmpword, a);

		list_addlast(wordlist, word);
	}

	list_sort(wordlist);
	// list_reverse(wordlist);

	void *tmp_item;
	while (list_size(wordlist) > 0) {
		tmp_item = list_popfirst(wordlist);
		printf("\t%3d, \"%s\"\n", ((word_t*)tmp_item)->freq, ((word_t*)tmp_item)->word);
	}
	printf("Map size: %d\n", map_size(map));
	// printf("Map maxsize: %d\n", map_maxsize(map));

    return 0;
}
