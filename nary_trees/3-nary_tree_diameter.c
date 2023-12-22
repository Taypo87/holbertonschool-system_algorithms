#include "nary_trees.h"

/**
 * update_top_two - updates top_two array with the greatest heights
 * @height: the height to check against the current top two heights
 * Return: the top two heights
*/
static size_t *update_top_two(size_t height)
{
	static size_t top_two[2] = {0}, temp = 0;


	if (temp > top_two[1])
		top_two[1] = temp;
	if (top_two[1] > top_two[0])
	{
		temp = top_two[0];
		top_two[0] = top_two[1];
		top_two[1] = temp;
	}
	return (&top_two);
}
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
 * get_height - gets the height of a given node
 * @root: root node of an nary tree
 * @diameter: pointer containing the diameter
 * Return: the diamter
*/
static size_t get_height(nary_tree_t *root)
{
	size_t max_height = 0, h = 0;
	nary_tree_t *temp;

	if (!root)
		return (0);
	
	for (temp = root->children; temp; temp = temp->children)
	{
		h = get_height(temp);
		if (h > max_height)
			max_height = h;
	}
	return (max_height + 1);
}

/**
 * nary_tree_diameter - get the diamter of an nary tree
 * @root: pointer to the root of a nary tree
 * Return: the diameter
*/
size_t nary_tree_diameter(nary_tree_t const *root)
{
	size_t *top_two, temp = 0;
	size_t root_diameter = 0, sub_diameter = 0;
	nary_tree_t *childs;

	if (!root)
		return (0);
	childs = (nary_tree_t *)root->children;
	for (;childs ; childs = childs->next);
	{
		temp = get_height(childs);
		top_two = update_top_two(temp);
	}	
	root_diameter = top_two[0] + top_two[1] + 1;
	childs = (nary_tree_t *)root->children;
	for (;childs ; childs = childs->next)
	{
		temp = nary_tree_diameter((nary_tree_t const *)childs);
		if (sub_diameter < temp)
			sub_diameter = temp;
	}
	return (root_diameter > sub_diameter ? root_diameter : sub_diameter);
}
