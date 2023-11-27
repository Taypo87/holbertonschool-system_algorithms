#include "heap.h"

/**
 * binary_tree_node - creates a new node for a heap
 * @parent: pointer to the parent node
 * @data: data to be stored in the node
 * Return: pointer to the newly created node
*/
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *new = calloc(1, sizeof(binary_tree_node_t));

	new->data = data;
	new->parent = parent;

	return (new);
}
