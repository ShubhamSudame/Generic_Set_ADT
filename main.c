#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

int size(void *a, int index);
int strsize(void *a, int index);

int main(int argc, char **argv) {
	if(argc != 3) {
		fprintf(stderr, "Usage: ./myprog <string_file> <integer_file>\n");
		return -1;
	}
	FILE *fp1, *fp2;
	fp1 = fopen(argv[1], "r");
	if(fp1 == NULL) {
		fprintf(stderr, "Failed to open file %s\n", argv[1]);
		return -2;
	}
	fp2 = fopen(argv[2], "r");
	if(fp2 == NULL) {
		fprintf(stderr, "Failed to open file %s\n", argv[2]);
		return -3;
	}
	int i, n1, n2;
	n1 = countlines(fp1);
	n2 = countlines(fp2);
	set l1, l2, l3, l4;
	init(&l1, n1);
	init(&l2, n2);
	char name[16] = {'\0'};
	while(fscanf(fp1, "%s", name) != EOF) {
		int size;
		size = strlen(name); /* If you're filling the set with strings, use strlen */
		insert(&l1, name, size);
	}
	removeblank(&l1);
	printf("The set of strings contains %d elements.\n", l1.n);
	for(i = 0; i < l1.n; i++) {
		printf("%s\n", (char *)l1.vertices[i]); /* This is how you typecast a string*/
	}
	printf("\n");
	int number;
	while(fscanf(fp2, "%d", &number) != EOF) {
		int size;
		size = sizeof(int); /* If you're filling the set with primitives, use sizeof operator */
		insert(&l2, &number, size);
	}
	removeblank(&l2);
	printf("The set of integers contains %d elements.\n", l2.n);
	for(i = 0; i < l2.n; i++) {
		printf("%d\n", *((int *)l2.vertices[i])); /* This is how you typecast a primitive*/
	}
	fclose(fp1);
	fclose(fp2);
	getsize(l1, strsize);
	getsize(l2, size);
	l3 = copy_set(l2, size);
	printf("The copy set of integers contains %d elements.\n", l3.n);
	for(i = 0; i < l3.n; i++) {
		printf("%d\n", *((int *)l3.vertices[i])); /* This is how you typecast a primitive*/
	}
	printf("\n");
	l4 = copy_set(l1, strsize);
	printf("The copy set of strings contains %d elements.\n", l4.n);
	for(i = 0; i < l4.n; i++) {
		printf("%s\n", (char *)l4.vertices[i]); /* This is how you typecast a string*/
	}
	printf("\n");

	set l5, U, I, D;
	init(&l5, 5);
	int j, digit;
	for(j = 0; j < l5.n; j++) {
		scanf("%d", &digit);
		insert(&l5, &digit, sizeof(int));
	}
	printf("The new set of integers l5 contains %d elements.\n", l5.n);
	for(i = 0; i < l5.n; i++) {
		printf("%d\n", *((int *)l5.vertices[i])); /* This is how you typecast a primitive*/
	}
	printf("\n");
	U = Union(l3, l5, size);
	printf("The Union set of integers contains %d elements.\n", U.n);
	for(i = 0; i < U.n; i++) {
		printf("%d\n", *((int *)U.vertices[i])); /* This is how you typecast a primitive*/
	}
	printf("\n");
	I = Intersection(l3, l5, size);
	printf("The Intersection set of integers contains %d elements.\n", I.n);
	for(i = 0; i < I.n; i++) {
		printf("%d\n", *((int *)I.vertices[i])); /* This is how you typecast a primitive*/
	}
	printf("\n");
	D = Difference(l3, l5, size);
	printf("The Difference set of integers contains %d elements.\n", D.n);
	for(i = 0; i < D.n; i++) {
		printf("%d\n", *((int *)D.vertices[i])); /* This is how you typecast a primitive*/
	}
	printf("\n");
	printf("Cardinality of set l1 = %d\n", cardinality(l1));
	if(is_subset(I, l5, size)) {
		printf("I is a subset of l5\n");
	}
	else
		printf("I is not a subset of l5\n");
	destruct(8, &l1, &l2, &l3, &l4, &l5, &U, &I, &D);
	return 0;
}

int size(void *a, int index) {
	int size = *((int *)a);
	return sizeof(size);
}

int strsize(void *a, int index) {
	int size;
	char *str = (char *)a;
	return size = strlen(str);
}

