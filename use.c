#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#include "dmp.h"


struct example {
	int a;
	char *b;
};

struct example2 {
	int a;
	char *b;
	int c;
	char d[18];
};

/******************************************************************************/
int main(int argc, char *argv[])
{
	struct dmp *memory;
	struct example ref, *test;
	struct example2 ref2, *test2;
	char *somestring = "somestring";
	long long int i;

	memory = dmp_new(2, sizeof(struct example), sizeof(struct example2));

	ref.a = 42;
	ref.b = somestring;
	ref2.a = 32;
	ref2.b = somestring;
	ref2.c = 4545;
	snprintf(ref2.d, 18, "balbablabla");

	for (i = 0; i < 4096; i++) {
		test = dmp_acquire(memory, sizeof(struct example));
		memcpy(test, (void *) &ref, sizeof(struct example));
	}

	for (i = 0; i < 10; i++) {
		test = dmp_acquire(memory, sizeof(struct example));
		memcpy(test, (void *) &ref, sizeof(struct example));
		dmp_release(memory, test);
		test2 = dmp_acquire(memory, sizeof(struct example2));
		memcpy(test2, (void *) &ref2, sizeof(struct example2));
		dmp_release(memory, test2);
	}

	dmp_delete(memory);

	return 0;
}

