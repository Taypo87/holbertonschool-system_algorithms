#include "heap.h"

static void deleter(binary_tree_node_t* node, void (*free_data)(void *))
{
    if (node->left)
        deleter(node->left, free_data);
    if (node->right)
        deleter(node->right, free_data);
    free_data(node->data);
    free(node);
    
}

void heap_delete(heap_t *heap, void (*free_data)(void *))
{
    deleter(heap->root, free_data);
}
