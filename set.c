#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "set.h"

void init(set *l, int n) {
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

void insert(set *l, void *data, int size) {
    if(!ispresent(l, data, size)) {
        int index;
        index = emptyentry(l);
        if(index != -1) {
            l->vertices[index] = calloc(1, sizeof(void *));
            memcpy(l->vertices[index], data, size);
        }
    }
}

int emptyentry(set *l) {
    int index;
    for(index = 0; index < l->n; index++) {
        if(l->vertices[index] == NULL) {
            return index;
        }
    }
    return -1;
}

int ispresent(set *l, void *data, int size) {
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

void removeblank(set *l) {
    int i, n;
    n = l->n;
    for(i = 0; i < n; i++) {
        if(l->vertices[i] == NULL) {
            free(l->vertices[i]);
            l->n--;
        }
    }
}

int vertex_index(set l, void *name, int size) {
    int i;
    for(i = 0; i < l.n; i++) {
        if(memcmp(l.vertices[i], name, size) == 0) {
            return i;
        }
    }
    return -1;
}

void destroy_set(set *l) {
	int i;
	for(i = 0; i < l->n; i++) {
		free(l->vertices[i]);
	}
	free(l->vertices);
}

void destruct(int count, ...) {
	va_list ap;
	int i;
	va_start(ap, count);
	for(i = 0; i < count; i++) {
		destroy_set(va_arg(ap, set *));
	}
	va_end(ap);
}

void getsize(set l, int (*len)(void *a, int index)) {
	int i;
	for(i = 0; i < l.n; i++) {
		printf("%d\n", len(l.vertices[i], i));
	}
}

set copy_set(set l, int(*len)(void *a, int index)) {
	set copy;
	init(&copy, l.n);
	int i, size;
	for(i = 0; i < l.n; i++) {
		size = len(l.vertices[i], i);
		insert(&copy, l.vertices[i], size);
	}
	return copy;
}

set Union(set A, set B, int (*len)(void *a, int index)) {
	set U;
	init(&U, A.n + B.n);
	int i, size;
	for(i = 0; i < A.n; i++) {
		size = len(A.vertices[i], i);
		insert(&U, A.vertices[i], size);
	}
	for(i = 0; i < B.n; i++) {
		size = len(B.vertices[i], i);
		insert(&U, B.vertices[i], size);
	}
	removeblank(&U);
	return U;
}

set Intersection(set A, set B, int (*len)(void *a, int index)) {
	set I;
	init(&I, A.n + B.n);
	int i, size;
	for(i = 0; i < A.n; i++) {
		size = len(A.vertices[i], i);
		if(ispresent(&B, A.vertices[i], size)) {
			insert(&I, A.vertices[i], size);
		}
	}
	removeblank(&I);
	return I;
}

set Difference(set A, set B, int (*len)(void *a, int index)) {
	set D;
	init(&D, A.n);
	int i, size;
	for(i = 0; i < A.n; i++) {
		size = len(A.vertices[i], i);
		if(!ispresent(&B, A.vertices[i], size)) {
			insert(&D, A.vertices[i], size);
		}
	}
	removeblank(&D);
	return D;
}
