#include "heap.h"
static binary_tree_node_t *node_swap(binary_tree_node_t *parent, binary_tree_node_t *node)
{
	binary_tree_node_t *temp;

	temp = parent;

	parent->left = node->left;
	parent->right = node->right;
	parent->parent = node;
	node->left = temp->left;
	node->right = temp->right;
	node->parent = temp->parent;
	return (parent);
}

static void value_check(binary_tree_node_t *node)
{
	binary_tree_node_t *temp;

	if (node->parent->data > node->data)
		node->parent = node_swap(node->parent, node);
	value_check(node->parent);
}

static binary_tree_node_t *insert_bottom_left(binary_tree_node_t *root, binary_tree_node_t *new_node)
{
	binary_tree_node_t *node = NULL;

	if(root->right && root->left)
	{
		insert_bottom_left(root->left, new_node);
		insert_bottom_left(root->right, new_node);
	}
	if (!root->left)
	{
		root->left = new_node;
		new_node->parent = root->left;
	}
	else if(root->left && !root->right)
	{
		root->right = new_node;
		new_node->parent = root->right;
	}
	return (new_node);
}

binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new;

	if(!data || !heap)
		return (NULL);
	
	new = binary_tree_node(NULL, data);
	if (!heap->root)
	{
		heap->root = new;
		return (new);
	}
	new = insert_bottom_left(heap->root, new);
	value_check(new);
	++heap->size;
	return(new);
}
