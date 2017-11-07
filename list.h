#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>

typedef struct list {
    void **vertices;
    int n;
} list;

int emptyentry(list *l);
int emptylist(void **list, int size);
int countlines(FILE *fp);
void init(list *l, int n);
void insert(list *l, void *data, int size);
int ispresent(list *l, void *data, int size);
void removeblank(list *l);
int vertex_index(list l, void *name);

#endif /* LIST_H_ */
