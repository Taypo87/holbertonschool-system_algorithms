#include "heap.h"
/**
 * deleter - recursive function that frees data and nodes of a heap
 * @node: the current node to free
 * @free_data: function that frees the data in a heap node
 * Return: VOID
*/
static void deleter(binary_tree_node_t* node, void (*free_data)(void *))
{
    if (!node)
        return;
    deleter(node->left, free_data);
    deleter(node->right, free_data);
    if (free_data)
        free_data(node->data);
    free(node);
    
}
/**
 * heap_delete - deletes a heap
 * 
*/
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
    deleter(heap->root, free_data);
    free(heap);
}
