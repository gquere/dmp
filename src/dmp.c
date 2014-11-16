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
#include <stdarg.h>
#include <semaphore.h>

#include "stack.h"
#include "dmp.h"


/******************************************************************************/
struct dmp * dmp_new(int count, ...)
{
    struct dmp *this = NULL;
    va_list ap;
    struct memory_pool *new, *current;
    int i;

    /* dmp is a pointer to a linked list of pools of various sizes */
    this = calloc(1, sizeof(struct dmp));
    if (this == NULL) {
        fprintf(stderr, "Error: Allocation failure in dmp_new()\n");
        return NULL;
    }

    /* read all sizes and create pools accordingly */
    va_start(ap, count);
    for (i = 0; i < count; i++) {
        new = calloc(1, sizeof(struct memory_pool));
        new->element_size = va_arg(ap, size_t) + sizeof(int);
        new->free_elements = stack_new();
        if (i == 0) {
            this->first = new;
        } else {
            current->next = new;
        }
        current = new;
    }
    va_end(ap);


    return this;
}

void dmp_delete(struct dmp *this)
{
    struct memory_pool *current, *tmp;

    current = tmp = this->first;
    while (current != NULL) {
        tmp = current->next;
        stack_delete(current->free_elements);
        free(current);
        current = tmp;
    }
}


/******************************************************************************/
struct memory_pool * identify_correct_pool(struct dmp *this, size_t element_size)
{
    struct memory_pool *correct_pool = this->first;

    /* identify correct pool based on size */
    while (correct_pool != NULL && correct_pool->element_size < element_size) {
        correct_pool = correct_pool->next;
    }

    return correct_pool;
}

void * dmp_acquire(struct dmp *this, size_t element_size)
{
    void *element = NULL;
    struct memory_pool *correct_pool = NULL;
    int *size;

    /* find pool which size matches that of the element */
    correct_pool = identify_correct_pool(this, element_size + sizeof(int));
    if (correct_pool == NULL) {
        fprintf(stderr, "Error: no matching pool for element size %d\n", element_size);
        return NULL;
    }

    /* try to get element from pool, otherwise allocate it */
    element = stack_pop(correct_pool->free_elements);
    if (element == NULL) {
        element = calloc(1, correct_pool->element_size);
        if (element == NULL) {
            fprintf(stderr, "Error: Allocation failure in dmp_acquire\n");
            return NULL;
        }
    } else {
        memset(element, 0, element_size);
    }

    /* write HIDDEN element size at begining */
    size = (int *) element;
    *size = element_size + sizeof(int);
    return element + sizeof(int);
}

int32_t dmp_release(struct dmp *this, void *element)
{
    struct memory_pool *pool = NULL;
    int *size = NULL;
    int *element_start;

    /* element size is hidden before the element */
    size = (int *) (element - sizeof(int));

    /* find pool to which element belongs */
    pool = identify_correct_pool(this, *size);
    if (pool == NULL) {
        fprintf(stderr, "Error: element of size %d has no matching pool\n", *size);
        return EXIT_FAILURE;
    }

    element_start = size;

    return stack_push(pool->free_elements, element_start);
}

