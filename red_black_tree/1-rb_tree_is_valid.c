#include "rb_trees.h"

static int is_bst_r(rb_tree_t *node, int *last_val);

/**
 * is_bst - wrapper for is_bst_r
 * @tree: root node pointer
 * Return: 1 if is bst, else 0
*/
static int is_bst(rb_tree_t *tree)
{
	int last_val = INT_MIN;

	return (is_bst_r(tree, &last_val));
}

/**
* is_bst_r - checks if a tree meets bst cirteria
* @node: pointer to a node in a tree
* @last_val: value of the previous node;
* Return: 1 if bst else 0
*/
static int is_bst_r(rb_tree_t *node, int *last_val)
{
	if (!node)
		return (1);
	if (!is_bst_r(node->left, last_val))
		return (0);
	if (*last_val >= node->n)
		return (0);
	*last_val = node->n;
	return (is_bst_r(node->right, last_val));
}

/**
 * color_check_r - checks node color, ensures red only have black connected
 * @node: root pointer in a tree, use root node to ensure proper checking
 * Return: 1 if tree uses Red_Black nodes in proper order, else 0
*/
static int color_check_r(rb_tree_t *node)
{
	if (!node)
		return (1);
	if(node->color == RED)
	{
		if (node->parent == NULL || node->parent->color == RED)
			return (0);

		if (node->left)
			if (node->left->color == RED)
				return (0);
		if (node->right)
			if (node->right->color == RED)
				return (0);
		if (!color_check_r(node->right))
			return (0);
		if (!color_check_r(node->left))
			return (0);		
	}
	return (1);

}
/**
 * check_black_height_r - checks the height of black nodes
 * @tree: pointer to the root node of a tree
 * Return: height of black nodes or zero if not blanced
*/
static int check_black_height_r(rb_tree_t *tree)
{
	int l_height, r_height, l_black = 0, r_black = 0;
	if (!tree)
		return (0);
	if (tree->left)
		if (tree->left->color == BLACK)
			l_black = 1;
	if (tree->right)
		if (tree->right->color == BLACK)
			r_black = 1;

	l_height = check_black_height_r(tree->left) + l_black;
	r_height = check_black_height_r(tree->right) + r_black;
	
	if (l_height != r_height)
		return (0);
	return (l_height);
	
}
/**
 * rb_tree_is_valid - checks if a tree is valid Red_Black Tree
 * @tree: pointer to the root node of a tree.
 * Return: 1 if valid tree, else 0
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	rb_tree_t *node;
	node = malloc(sizeof(rb_tree_t));
	*node = *tree;

	if (is_bst(node) && color_check_r(node) && check_black_height_r(node))
	{
		free(node);
		return (1);
	}
	free(node);
	return (0);
}
