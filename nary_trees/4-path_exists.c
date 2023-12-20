#include "nary_trees.h"

/**
 * path_exists - checks if a path exists in an nary tree
 * @root: pointer to the root node of an nary tree
 * @path: null terminated array of strings containing the path
 * Return: 1 if path exists, else 0
*/
int path_exists(nary_tree_t const *root, char const * const *path)
{
	nary_tree_t *temp;
	int i, on_path;

	temp = (nary_tree_t *)root;
	temp = root->children;
	for  (i = 0 ; path[i]; i++)
	{
		on_path = 0;
		while (temp)
		{
			if (strcmp(path[i], temp->content) == 0)
			{
				temp = temp->children;
				on_path = 1;
			}
			if (on_path)
				break;
			else 
				temp = temp->next;
		}
		if (!on_path)
			return (0);
	}
	return (1);
}
