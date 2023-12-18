#include "nary_trees.h"
/**
 * nary_tree_delete - frees an nary tree
 * @tree: pointer to the root of an nary tree
*/
void nary_tree_delete(nary_tree_t *tree)
{
	nary_tree_t *temp;
	
	if (!tree)
		return;
	if (tree->children)
		nary_tree_delete(tree->children);
	if (tree->next)
	{
		nary_tree_delete(tree->next);
	}
	free(tree->content);
	free(tree);
	return;
}
