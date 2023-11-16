#include "rb_trees.h"

rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
    size_t i = 0;
    rb_tree_t *node;

    while (i < size)
    {
        rb_tree_insert(&node, array[i]);
        i++;
    }
    return (node);
}
