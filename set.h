#ifndef SET_H_
#define SET_H_

#include <stdio.h>

typedef struct set {
    void **vertices;
    int n;
} set;

int emptyentry(set *l);
int emptylist(void **list, int size);
int countlines(FILE *fp);
void init(set *l, int n);
void insert(set *l, void *data, int size);
int ispresent(set *l, void *data, int size);
void removeblank(set *l);
int vertex_index(set l, void *name);
void destroy_set(set *l);
void destruct(int count, ...);

#endif /* SET_H_ */
