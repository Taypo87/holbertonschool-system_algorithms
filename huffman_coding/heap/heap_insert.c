#include "heap.h"

/**
 * node_swap - swaps two nodes' data
 * @parent: pointer to the parent node
 * @node: pointer to the current node
 * Return: the current node
*/
binary_tree_node_t *node_swap(binary_tree_node_t *parent,
										 binary_tree_node_t *node)
{
	void *temp;

	temp = parent->data;
	parent->data = node->data;
	node->data = temp;

	return (parent);
}
/**
 * value_check - checks if the values are in proper order, calls swap
 * @heap: pointer to the heap
 * @node: pointer to the current node
 * Return: a pointer to the current node
*/

binary_tree_node_t *value_check(heap_t *heap, binary_tree_node_t *node)
{

	while (node->parent)
	{
		if (heap->data_cmp(node->data, node->parent->data) <= 0)
			node = node_swap(node->parent, node);
		else
			break;
	}
	return (node);
}

/**
 * insert_bottom_left - inserts a new node and the lower left most available
 * @root: pointer to the root of a binary tree
 * @new_node: pointer to the newly created node
 * Return: pointer to the new node
*/
static binary_tree_node_t *insert_bottom_left(binary_tree_node_t *root,
												 binary_tree_node_t *new_node)
{
	binary_tree_node_t *queue[100];

	int insertion = -1, operation = 0;

	queue[++insertion] = root;
	for (; ; operation++)
	{
		if (!queue[operation]->left)
		{
			new_node->parent = queue[operation];
			queue[operation]->left = new_node;
			break;
		}
		else if (!queue[operation]->right)
		{
			new_node->parent = queue[operation];
			queue[operation]->right = new_node;
			break;
		}
		else
		{
			queue[++insertion] = queue[operation]->left;
			queue[++insertion] = queue[operation]->right;
		}
	}

	return (new_node);
}
/**
 * heap_insert - inserts a new node into a heap
 * @heap: pointer to the top of the heap
 * @data: data to be stored in the new node
 * Return: pointer to the new node
*/
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new;


	if (!data || !heap)
		return (NULL);

	new = binary_tree_node(NULL, data);
	if (!heap->root)
	{
		heap->root = new;
		++heap->size;
		return (new);
	}
	new = insert_bottom_left(heap->root, new);
	if (new->parent)
		value_check(heap, new);
	++heap->size;
	return (new);
}
