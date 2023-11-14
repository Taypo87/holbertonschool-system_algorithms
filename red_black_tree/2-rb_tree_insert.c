#include "rb_trees.h"

int static gather_family(rb_tree_t **family, rb_tree_t *new);
static rb_tree_t *get_uncle(rb_tree_t *tree_pos, int *is_outer);
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
    tree = new_root;

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
    tree = new_root;

	return (new_root);
}


/**
 * bst_insert - inserts a node in order on a given tree 
 * @root: pointer to the root node of a tree
 * @new: double pointer to the newly created node
 * Return: pointer to the newly created node
*/
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
/**
 * in_attendance - checks if all family members are present for counseling
 * @family: double pointer to the related pointers
 * Return: 1 is valid pointers, else 0
*/
static int in_attendance(rb_tree_t **family)
{
    if(family[1] && family[2] && family[3])
        return(1);
    else
        return (0);
}
/**
 * family_counseling - fixes a red-black tree after new node is added
 * @root: pointer to the root of a tree
 * @new: the newly created node that was inserted
 * Return: pointer to the root of the tree
*/
static rb_tree_t *family_counseling(rb_tree_t *root, rb_tree_t *new)
{
    rb_tree_t *parent_pointer = NULL, *uncle = NULL, *grandparent = NULL, *tree_pos = NULL, **family = NULL;
    int is_outer;
    
    family = (rb_tree_t *[]){tree_pos, parent_pointer, uncle, grandparent};
    gather_family(family, new);
 out:   /*counseling session to remediate family(reb-black)tree problems*/
    while (in_attendance(family))
    {
        // case 1
        if (parent_pointer->color == BLACK)
            return(root);
        // case 2
        if (parent_pointer->color == RED && uncle->color == RED)
        {
            parent_pointer->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            is_outer = gather_family(family, new);
            goto out;
        }
        //case 5
        if (parent_pointer->color == RED && uncle->color == BLACK && !is_outer)
        {
            right_rotate(parent_pointer);
            tree_pos = parent_pointer;
            parent_pointer = grandparent->left;
            is_outer = 1;

        }
        //case 6
        if (parent_pointer->color == RED && uncle->color == BLACK && is_outer)
        {
            left_rotate(grandparent);
            parent_pointer->color = BLACK;
            grandparent->color = RED;
            grandparent = parent_pointer;
        }
        is_outer = gather_family(family, new);
    }
    // case 4
    if(parent_pointer)
        if (!grandparent && parent_pointer->color == RED)
            parent_pointer->color = BLACK;
    else
        tree_pos->color = BLACK;
    return (tree_pos);
}
/**
 * update_family - updates all our "related" pointers
 * @family: 0 = tree_pos, 1 = parent_pointer, 2 = uncle, 3 = grandparent
 * @new: the newly created node that we added
 * Return: the is_outer truth value
*/
int static gather_family(rb_tree_t **family, rb_tree_t *new)
{
        int is_outer;
        /*tree_pos*/
        if (family[0])
            family[0] = family[3];
        else 
            family[0] = new;
        /*parent*/
        if (family[0]->parent)
            family[1] = family[0]->parent;
        else
        {
            family[1] = NULL;
        }
        /*uncle*/
        family[2] = get_uncle(family[0], &is_outer);
        /*grandparent*/
        if(family[1])
            if (family[1]->parent)
                family[3] = family[1]->parent;
        else
        {
            family[3] = NULL;
        }
        return (is_outer);
}

static rb_tree_t *get_uncle(rb_tree_t *tree_pos, int *is_outer)
{
    if (!tree_pos->parent)
        return (NULL);
    if (!tree_pos->parent->parent)
        return (NULL);
    if (tree_pos->parent->parent->left == tree_pos->parent)
    {
        *is_outer = 1;
        return (tree_pos->parent->parent->right);
    }
        
    else
    {
        *is_outer = 0;
        return (tree_pos->parent->parent->left);
    }
        
}

/**
 * rb_tree_insert - inserts a node following Red Black tree requirments
 * @tree: double pointer to the root of a given tree
 * @value: value to be stored in the newly created node
 * Return: pointer to the newly created node
*/
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
    rb_tree_t *node, *new;

    node = *tree;
    new = rb_tree_node(NULL, value, RED);
    node = bst_insert(node, &new);
    *tree = family_counseling(node, new);
    return (new);
}
