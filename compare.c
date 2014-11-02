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
	struct example ref, *test;
	char *somestring = "somestring";
	int i;

	ref.a = 42;
	ref.b = somestring;

	for (i = 0; i < 4096; i++) {
		test = calloc(1, sizeof(struct example));
		memcpy(test, (void *) &ref, sizeof(struct example));
		free(test);
	}

	for (i = 0; i < 100000000; i++) {
		test = calloc(1, sizeof(struct example));
		memcpy(test, (void *) &ref, sizeof(struct example));
		free(test);
	}

	return 0;
}

