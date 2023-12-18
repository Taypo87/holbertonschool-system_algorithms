#include "nary_trees.h"
/**
 * nary_tree_insert - inserts a newly created node into an nary tree
 * @parent: the parent node of the the new node
 * @str: the data to be stored in the new node
 * Return: pointer to the newly created node
*/
nary_tree_t *nary_tree_insert(nary_tree_t *parent, char const *str)
{
	nary_tree_t *node = calloc(sizeof(nary_tree_t), 1);

	node->content = strdup(str);
	node->parent = parent;
	if (parent)
	{
		node->next = parent->children;
		parent->children = node;
	}
	return (node);
}
