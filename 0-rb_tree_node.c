#include "rb_trees.h"

/**
 * rb_tree_node - creates a new node for a RB tree
 * @parent: pointer to parent node of the newly created node
 * @value: the value to be stored in the new node
 * @color: color of the newly created node
 * Return: pointer to the new node, NULL on error
*/

rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
    rb_tree_t *new;

    new = malloc(sizeof(rb_tree_t));
    if (!new)
        return (NULL);
    new->parent = parent;
    new->n = value;
    new->color = color;
    new->left = NULL;
    new->right = NULL;

    return (new);
}
