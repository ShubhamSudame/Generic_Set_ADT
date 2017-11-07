#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

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
	set l1, l2;
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
	//destroy_set(&l1);
	//destroy_set(&l2);
	destruct(2, &l1, &l2);
	return 0;
}

