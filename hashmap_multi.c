#include <stdlib.h>
#include "map.h"
#include "list.h"
#include <string.h>
#include <math.h>

#define BASE 20
int *global_idx; 

typedef struct mapnode {
	void *key;
	void *val;
} mapnode_t;

struct map {
	mapnode_t **********************hashtable;
	int size;
	cmpfunc_t cmpfunc;
	hashfunc_t hashfunc;
};

void error_check(void *input) {
	if (input == NULL) fatal_error("ERROR\n");
}

mapnode_t *map_new_node(void *key, void *val) {
	mapnode_t *newnode = malloc(sizeof(mapnode_t));
	error_check(newnode);
	newnode->key = key;
	newnode->val = val;
	return newnode;
}

map_t *map_create(cmpfunc_t cmpfunc, hashfunc_t hashfunc) {
	map_t *map = malloc(sizeof(map_t));
	error_check(map);
	map->size = 0;
	map->hashtable = calloc(sizeof(mapnode_t **********************), 10);
	map->cmpfunc = cmpfunc;
	map->hashfunc = hashfunc;
	return map;
}

int map_size(map_t *map) {
	return map->size;
}
// void map_destroy(map_t *map) {
// 	for (int i = 0; i < map->idx_size; i++) {
// 		if (map->hashtable[i] != NULL) {
// 			while (list_size(map->hashtable[i]) > 0)
// 				free(list_poplast(map->hashtable[i]));
// 			list_destroy(map->hashtable[i]);
// 		}
// 	}
// 	free(map->hashtable);
// 	free(map);
// }

mapnode_t *map_get_node(map_t *map, int *idx) {
	return map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]][idx[20]];
}

mapnode_t **map_get_node_arr(map_t *map, int *idx) {
	return map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]];
}

void map_put(map_t *map, void *key, void *val) {
	unsigned long hashval = map->hashfunc(key);
	int haskey = map_haskey(map, key);
	int *idx = global_idx;

	if (haskey == 0 || haskey == -1) {
		if (haskey == -1) {
			int i = 0, a = 0;

			mapnode_t **node = map_get_node_arr(map, idx);
			for (i; node[i] != NULL; i++);

			mapnode_t **tmp = calloc(i + 1, sizeof(mapnode_t *));
			for (a; a < i; a++) tmp[a + 1] = node[a];

			map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]] = tmp;
			free(node);
		}
		if (haskey == 0) map_malloc(map, idx);
		mapnode_t *new = map_new_node(key, val);
		mapnode_t **node = map_get_node_arr(map, idx);
		node[0] = new;
		map->size++;
	}
	else {
		mapnode_t *node = map_get_node(map, idx);
		node->val = val;
	}
}

int map_haskey(map_t *map, void *key) {
	unsigned long hashval = map->hashfunc(key);
	if (global_idx != NULL) global_idx = calloc(BASE + 1, sizeof(int));
	global_idx = map_get_idx(hashval);
	if (map_check_idx(map, global_idx) == 0) return 0;

	mapnode_t **node = map_get_node_arr(map, global_idx);
	for(int i = 0; node[i] != NULL; i++) {
		if (map->cmpfunc(node[i]->key, key) == 0) {
			global_idx[BASE] = i;
			return 1;
		}
	}
	return -1;
}

void *map_get(map_t *map, void *key) {
	unsigned long hashval = map->hashfunc(key);
	int haskey = map_haskey(map, key);
	if (haskey == 0) return 0;

	int *idx = global_idx;
	mapnode_t *node = map_get_node(map, idx);
	printf ("map->hashtable[%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d][%d]: Val = %d\tKey = %s\n", idx[0], idx[1], idx[2], idx[3], idx[4], idx[5], idx[6], idx[7], idx[8], idx[9], idx[10], idx[11], idx[12], idx[13], idx[14], idx[15], idx[16], idx[17], idx[18], idx[19], idx[20], *(int *)map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]][idx[20]]->val, map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]][idx[20]]->key);
	return node->val;
}

int *map_get_idx(unsigned long input) {
	int *idx = calloc(BASE + 1, sizeof(int));
	char buffer[BASE];
	sprintf(buffer, "%lu", input); 
	int len = strlen(buffer), e;

	if (len < BASE) {
		char *tmp = strdup(buffer);
		for (int i = 0; i < BASE - len; i++) buffer[i] = '0';
		for (int i = 0; i < len; i++) buffer[(BASE - len) + i] = tmp[i];
	}

	for (e = 0; e < BASE; e++) idx[e] = buffer[e] - '0';
	idx[e] = 0;
	return idx;
}

int map_check_idx(map_t *map, int *idx) {
	if (map->hashtable[idx[0]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]] == NULL) return 0;
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]][idx[20]] == NULL) return 0;
	return 1;
}

void map_malloc(map_t *map, int *idx) {
	if (map->hashtable == NULL) map->hashtable																																														= calloc(BASE, sizeof(void *********************));
	if (map->hashtable[idx[0]] == NULL) map->hashtable[idx[0]]																																										= calloc(BASE, sizeof(void ********************));
	if (map->hashtable[idx[0]][idx[1]] == NULL) map->hashtable[idx[0]][idx[1]]																																						= calloc(BASE, sizeof(void *******************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]]																																		= calloc(BASE, sizeof(void ******************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]]																														= calloc(BASE, sizeof(void *****************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]]																										= calloc(BASE, sizeof(void ****************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]]																						= calloc(BASE, sizeof(void ***************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]]																		= calloc(BASE, sizeof(void **************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]]														= calloc(BASE, sizeof(void *************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]]										= calloc(BASE, sizeof(void ************));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]] 						= calloc(BASE, sizeof(void ***********));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]]	= calloc(BASE, sizeof(void **********));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]]																															= calloc(BASE, sizeof(void *********));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]]																												= calloc(BASE, sizeof(void ********));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]]																										= calloc(BASE, sizeof(void *******));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]]																								= calloc(BASE, sizeof(void ******));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]]																						= calloc(BASE, sizeof(void *****));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]]																			= calloc(BASE, sizeof(void ****));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]]																	= calloc(BASE, sizeof(void ***));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]]															= calloc(BASE, sizeof(void **));
	if (map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]] == NULL) map->hashtable[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]][idx[5]][idx[6]][idx[7]][idx[8]][idx[9]][idx[10]][idx[11]][idx[12]][idx[13]][idx[14]][idx[15]][idx[16]][idx[17]][idx[18]][idx[19]]													= calloc(BASE, sizeof(void *));
}

