/* Description: One single node */

#include <stdlib.h>
#include <stdio.h>

#include "nary_trees.h"

void nary_tree_delete(nary_tree_t *tree);

void _print_node(nary_tree_t const *node, size_t depth)
{
	printf("%*s%s\n", (int)depth * 2, "", node->content);
}

int main(void)
{
	nary_tree_t *root;
	size_t diameter;

	root = nary_tree_insert(NULL, "/");
	if (!root)
	{
		fprintf(stderr, "Failed to create node\n");
		return (EXIT_FAILURE);
	}

	nary_tree_traverse(root, &_print_node);
	diameter = nary_tree_diameter(root);
	printf("Diameter = %lu\n", diameter);

	nary_tree_delete(root);

	return (EXIT_SUCCESS);
}