#include "rb_trees.h"

/**
 * binary_tree_rotate_left - balances a tree by rotating nodes left
 * @tree: pointer to the root of a tree
 * Return: pointer to the new root
*/

static rb_tree_t *left_rotate(rb_tree_t *tree)
{
	rb_tree_t *new_root, *old_root, *old_left;

	if (tree == NULL || tree->right == NULL)
		return (tree);

	old_root = tree;
	new_root = tree->right;
	if (tree->right->left)
	{
		old_left = tree->right->left;
		old_left->parent = old_root;
		old_root->right = old_left;
	}
	else
		old_root->right = NULL;
	if (old_root->parent)
	{
		if (old_root == old_root->parent->left)
		{
			old_root->parent->left = new_root;
		}
		else
			old_root->parent->right = new_root;
	}
	new_root->parent = old_root->parent;
	old_root->parent = new_root;
	new_root->left = old_root;

	return (new_root);
}

/**
 * binary_tree_rotate_right - balances a tree by rotating nodes right
 * @tree: pointer to the root of a tree
 * Return: pointer to the new root
*/


static rb_tree_t *right_rotate(rb_tree_t *tree)
{
	rb_tree_t *old_root, *new_root, *old_right;

	if (tree == NULL || tree->left == NULL)
		return (tree);

	old_root = tree;
	new_root = tree->left;
	if (tree->left->right)
	{
		old_right = tree->left->right;
		old_right->parent = old_root;
		old_root->left = old_right;
	}
	else
		old_root->left = NULL;
	if (old_root->parent)
	{
		if (old_root == old_root->parent->left)
		{
			old_root->parent->left = new_root;
		}
		else
			old_root->parent->right = new_root;
	}
	new_root->parent = tree->parent;
	new_root->right = old_root;
	old_root->parent = new_root;

	return (new_root);
}

/**
 * insert_fixup - changes colors and rotates a tree until it meets rb specs
 * @root: pointer to the root of a tree
 * @new: the newly created node that was inserted
 * Return: pointer to the root of the tree
*/

static rb_tree_t *insert_fixup(rb_tree_t *root, rb_tree_t *new)
{
    rb_tree_t *uncle;

    if (new->parent)
    {
        while (new->parent->color == RED)
        {
            if (new->parent == new->parent->parent->left)
            {
                uncle = new->parent->parent->right;
                if (uncle->color == RED)
                {
                    new->parent->color = BLACK;
                    uncle->color = BLACK;
                    new->parent->parent->color = RED;
                    new = new->parent->parent;
                }
                else if (new == new->parent->right)
                {
                    new = new->parent;
                    left_rotate(root);
                }
                if (new->parent)
                {
                    new->parent->color = BLACK;
                    if (new->parent->parent)
                        new->parent->parent->color = RED;
                }
                right_rotate(root);        
            }
            else
            {
                root->color = BLACK;
            }
        }
    }
    else
    new->color = BLACK;
    return (root);
}
static rb_tree_t *bst_insert(rb_tree_t *root, rb_tree_t **new)
{
    if (!new)
		return (NULL);
	if (!root)
	{
		root = *new;
		return (root);
	}
	if ((*new)->n == root->n)
	{
		free(*new);
		*new = root;
		return (root);
	}
	(*new)->parent = root;
	if ((*new)->n > root->n)
		root->right = bst_insert(root->right, new);
	else
		root->left = bst_insert(root->left, new);

    if (root->right)
        root->right->parent = root;
    if (root->left)
        root->left->parent = root;
    return (root);

}

rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
    rb_tree_t *node, *new;

    node = *tree;
    new = rb_tree_node(NULL, value, RED);
    node = bst_insert(node, &new);
    node = insert_fixup(node, new);
    *tree = node;
    return (node);
}
