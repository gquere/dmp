/**
 * @file: queue.c
 * Simple queue that holds pointers to elements using a ring buffer
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "queue.h"

/******************************************************************************/
struct queue * queue_new(void)
{
	struct queue *this = NULL;

	this = calloc(1, sizeof(struct queue));
	if (this == NULL) {
		fprintf(stderr, "Error: Allocation failure in queue_new()\n");
		return NULL;
	}

	this->nb_elems = 0;
	this->current_write = 0;
	this->current_read = 0;

	return this;
}

void queue_delete(struct queue *this)
{
	int i = 0;
	int j = 0;

	j = this->current_read;
	for (i = 0; i < this->nb_elems; i++) {
		free(this->elems[j]);
		j++;
		if (j == MAX_QUEUE_SIZE) {
			j = 0;
		}
	}

	free(this);
}


/******************************************************************************/
/**
 * Push an address in the queue
 *
 * @param this		queue object
 * @param elem_addr	address to push in queue
 * @return		EXIT_SUCCESS on succes, EXIT_FAILURE otherwise
 */
int32_t queue_push(struct queue *this, void *elem_addr)
{
	if (this->nb_elems >= MAX_QUEUE_SIZE) {
		fprintf(stderr, "Error: Stack is full\n");
		return EXIT_FAILURE;
	}

	this->elems[this->current_write] = elem_addr;
	this->nb_elems++;
	this->current_write++;
	if (this->current_write == MAX_QUEUE_SIZE) {
		this->current_write = 0;
	}

	return EXIT_SUCCESS;
}

/**
 * Pop an element from the queue
 *
 * @param this	queue object
 * @return	elem address on success, NULL otherwise
 */
void * queue_pop(struct queue *this)
{
	void *return_addr;

	if (this->nb_elems == 0 || this->current_read == -1) {
		return NULL;
	}

	return_addr = this->elems[this->current_read];
	this->nb_elems--;
	this->current_read++;

	return return_addr;
}

