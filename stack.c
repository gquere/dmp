/**
 * @file: stack.c
 * Simple stack that holds pointers to elements
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"

/******************************************************************************/
struct stack * stack_new(void)
{
	struct stack *this = NULL;

	this = calloc(1, sizeof(struct stack));
	if (this == NULL) {
		fprintf(stderr, "Error: Allocation failure in stack_new()\n");
		return NULL;
	}

	this->nb_elems = 0;

	return this;
}

void stack_delete(struct stack *this)
{
	int i = 0;

	for (i = 0; i < this->nb_elems; i++) {
		free(this->elems[i]);
	}

	free(this);
}


/******************************************************************************/
/**
 * Push an address in the stack
 *
 * @param this		stack object
 * @param elem_addr	address to push in stack
 * @return		EXIT_SUCCESS on succes, EXIT_FAILURE otherwise
 */
int32_t stack_push(struct stack *this, void *elem_addr)
{
	if (this->nb_elems >= MAX_STACK_SIZE) {
		fprintf(stderr, "Error: Stack is full, drop element\n");
		free(elem_addr);
        return EXIT_FAILURE;
	}

	this->elems[this->nb_elems] = elem_addr;
	this->nb_elems++;

	return EXIT_SUCCESS;
}

/**
 * Pop an element from the stack
 *
 * @param this	stack object
 * @return	elem address on success, NULL otherwise
 */
void * stack_pop(struct stack *this)
{
	void *return_addr;

	if (this->nb_elems == 0) {
		return NULL;
	}

	return_addr = this->elems[this->nb_elems-1];
	this->nb_elems--;

	return return_addr;
}

