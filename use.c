#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmp.h"


struct example {
	int a;
	char *b;
};


/******************************************************************************/
int main(int argc, char *argv[])
{
	struct dmp *memory;
	struct example ref, *test;
	char *somestring = "somestring";
	int i;

	memory = dmp_new(sizeof(struct example));

	ref.a = 42;
	ref.b = somestring;

	for (i = 0; i < 4096; i++) {
		test = dmp_acquire(memory);
		memcpy(test, (void *) &ref, sizeof(struct example));
	}

	for (i = 0; i < 100000000; i++) {
		test = dmp_acquire(memory);
		memcpy(test, (void *) &ref, sizeof(struct example));
		dmp_release(memory, test);
	}

	dmp_delete(memory);

	return 0;
}

