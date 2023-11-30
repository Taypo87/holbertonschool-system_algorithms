#include "heap.h"

void *heap_extract(heap_t *heap)
{
    binary_tree_node_t *root;

    root = heap->root;
    
    if (!root)
        root = NULL;

    return(NULL);
}