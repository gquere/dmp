/**
 * @file: dmp.c
 * Dynamic Memory Pool
 * Stack of dynamically allocated elements used as a malloc replacement
 * for time-constrained applications
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "stack.h"
#include "dmp.h"


/******************************************************************************/
struct dmp * dmp_new(size_t element_size)
{
	struct dmp *this = NULL;

	this = calloc(1, sizeof(struct dmp));
	if (this == NULL) {
		fprintf(stderr, "Error: Allocation failure in dmp_new()\n");
		return NULL;
	}

	this->free_elements = stack_new();
	this->element_size = element_size;

	return this;
}

void dmp_delete(struct dmp *this)
{
	stack_delete(this->free_elements);
	free(this);
}


/******************************************************************************/
void * dmp_acquire(struct dmp *this)
{
	void *element = NULL;

	element = stack_pop(this->free_elements);
	if (element == NULL) {
		element = calloc(1, this->element_size);
		if (element == NULL) {
			fprintf(stderr, "Error: Allocation failure in dmp_acquire\n");
		}
	}

    memset(element, 0, this->element_size);
	return element;
}

// FIXME: propagation ?
int32_t dmp_release(struct dmp *this, void *element)
{
	return stack_push(this->free_elements, element);
}

