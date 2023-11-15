#include "rb_trees.h"

static int gather_family(rb_tree_t *tree_pos, rb_tree_t **parent, rb_tree_t **uncle, rb_tree_t **gp);
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
		return (*new);
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
static int in_attendance(rb_tree_t *parent, rb_tree_t *uncle, rb_tree_t *grandparent)
{
    if(parent && uncle && grandparent)
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
    rb_tree_t *parent_pointer = NULL, *uncle = NULL, *grandparent = NULL, *tree_pos = NULL; 
    int is_outer;

    tree_pos = new;
    gather_family(tree_pos, &parent_pointer, &uncle, &grandparent);
 out:   /*counseling session to remediate family(reb-black)tree problems*/
    while (in_attendance(parent_pointer, uncle, grandparent))
    {
        // case 1
        if (parent_pointer->color == BLACK)
        {
            return (tree_pos);
        }
            
        // case 2
        //printf("uncle 2 value is %d\n", uncle->n);
        if (parent_pointer->color == RED && uncle->color == RED)
        {
            //printf("4th node should put us here %d\n", uncle->n);
            parent_pointer->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            tree_pos = grandparent;
            is_outer = gather_family(tree_pos, &parent_pointer, &uncle, &grandparent);
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
            grandparent = left_rotate(grandparent);
            parent_pointer->color = BLACK;
            grandparent->color = RED;
            grandparent = parent_pointer;
        }
        tree_pos = grandparent;
        is_outer = gather_family(tree_pos, &parent_pointer, &uncle, &grandparent);
    }
    // case 4
    if(parent_pointer)
    {
        if (parent_pointer->color == RED)
        {
            parent_pointer->color = BLACK;
            if(!grandparent)
                return (parent_pointer);
            else
                return (grandparent);
        }
    }
    else
        tree_pos->color = BLACK;
    
    if(grandparent)
        root = grandparent;
    else if (parent_pointer)
        root = parent_pointer;
    else 
        root = tree_pos;
    
    return (root);
}
/**
 * update_family - updates all our "related" pointers
 * @family: 0 = tree_pos, 1 = parent_pointer, 2 = uncle, 3 = grandparent
 * @new: the newly created node that we added
 * Return: the is_outer truth value
*/
static int gather_family(rb_tree_t *tree_pos, rb_tree_t **parent, rb_tree_t **uncle, rb_tree_t **gp)
{
        int is_outer;
        
        /*parent*/
        if (tree_pos->parent)
            *parent = tree_pos->parent;
        else
        {
            *parent = NULL;
        }
        /*uncle*/
        *uncle = get_uncle(tree_pos, &is_outer);
        if(!*uncle)
            *uncle = NULL;
        /*grandparent*/
        if(*parent)
        {
            if ((*parent)->parent)
                *gp = (*parent)->parent;
        }
        else
        {
            *gp = NULL;
        }
        if (!*gp)
            *gp = NULL;
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
    node = family_counseling(node, new);
    *tree = node;
    if (!node)
        printf("problem with root node not getting updated\n");
    if (!new)
        printf("problem with new node in gather family\n");
    if (!(*tree))
        printf("tree pointer wasn't updated\n");
    return (new);
}
