#include "nary_trees.h"

/**
 * max - returns the greater value of x and y
 * x: first value
 * y: second value
 * Return:the greater value
*/
static size_t max(size_t x, size_t y)
{
	return (x > y ? x : y);
}
/**
 * get_height - gets the path lenght of a given node
 * @root: root node of an nary tree
 * @diameter: pointer containing the diameter
 * Return: the diamter
*/
static size_t get_height(nary_tree_t *root, size_t *diameter)
{
	int maxHeight1 = 0, maxHeight2 = 0;
	nary_tree_t *temp;
	if (root == NULL) return 0;

	temp = root->children;
	while (temp != NULL) {
		int childHeight = findHeight(temp->children, diameter);

		if (childHeight > maxHeight1) {
			maxHeight2 = maxHeight1;
			maxHeight1 = childHeight;
		} else if (childHeight > maxHeight2) {
			maxHeight2 = childHeight;
		}

		temp = temp->next;
	}

	// Update diameter at this node
	*diameter = max(*diameter, maxHeight1 + maxHeight2);

	return maxHeight1 + 1;
}

/**
 * nary_tree_diameter - get the diamter of an nary tree
 * @root: pointer to the root of a nary tree
 * Return: the diameter
*/
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t diameter = 0;
	get_height((nary_tree_t *)root, &diameter);
	return (diameter);

}
