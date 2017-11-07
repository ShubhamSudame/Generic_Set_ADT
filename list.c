#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void init(list *l, int n) {
    l->vertices = calloc(n, sizeof(void *));
    l->n = n;
}
int emptylist(void **list, int size) {
    int i;
    for(i = 0; i < size; i++) {
        if(list[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int countlines(FILE *fp) {
	int c, n = 0;
	while((c = fgetc(fp)) != EOF) {
		if(c == '\n')
			n++;
	}
	rewind(fp);
	return n;
}

void insert(list *l, void *data, int size) {
    if(!ispresent(l, data, size)) {
        int index;
        index = emptyentry(l);
        if(index != -1) {
            l->vertices[index] = calloc(1, sizeof(void *));
            memcpy(l->vertices[index], data, size);
        }
    }
}

int emptyentry(list *l) {
    int index;
    for(index = 0; index < l->n; index++) {
        if(l->vertices[index] == NULL) {
            return index;
        }
    }
    return -1;
}

int ispresent(list *l, void *data, int size) {
    if(emptylist(l->vertices, l->n)) {
        return 0;
    }
    int i;
    for(i = 0; i < l->n; i++) {
        if((l->vertices[i] != NULL)) {
            if(memcmp(l->vertices[i], data, size) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void removeblank(list *l) {
    int i, n;
    n = l->n;
    for(i = 0; i < n; i++) {
        if(l->vertices[i] == NULL) {
            free(l->vertices[i]);
            l->n--;
        }
    }
}

int vertex_index(list l, void *name) {
    int i;
    for(i = 0; i < l.n; i++) {
        if(memcmp(l.vertices[i], name, sizeof(void *)) == 0) {
            return i;
        }
    }
    return -1;
}


