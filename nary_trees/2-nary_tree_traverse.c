#include "nary_trees.h"
typedef void (*action_t)(const nary_tree_t *node, size_t depth);


/**
 * traverse_recurs - traverses an nary tree recursively
 * @node: a node in the nary tree
 * @depth: the current depth of the node
 * @fp: function pointer containing the action to be performed
 * Return: the current depth
*/
static size_t traverse_recurs(nary_tree_t *node, size_t depth, action_t fp)
{
	nary_tree_t *childs;

	if (!node)
		return (depth);
	fp(node, depth);

	childs = node->children;
	while (childs)
	{
		traverse_recurs(childs, depth + 1, fp);
		childs = childs->next;
	}
	return (depth);
}

/**
 * nary_tree_traverse - wrapper function for traverse recurse
 * @root: root node of the nary tree
 * @action: function pointer to be perform on each node
 * Return: the max depth
*/
size_t nary_tree_traverse(nary_tree_t const *root,
void (*action)(nary_tree_t const *node, size_t depth))
{
	action_t fp = action;
	size_t current_depth = 0;

	current_depth = traverse_recurs((nary_tree_t *)root, current_depth, fp);
	return (current_depth);
}
