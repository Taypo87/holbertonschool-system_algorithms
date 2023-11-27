#include "heap.h"

/**
 * heap_create - creates a new heap struct
 * @data_cmp: compares to pointers
 * Return: pointer to the newly created heap
*/
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *new = NULL;

	new->data_cmp = data_cmp;
	new->root = NULL;
	new->size = 0;

	return (new);
}
