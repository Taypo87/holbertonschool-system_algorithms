#include "heap.h"

/**
 * get_last_node - finds the location of the last node in a heap
 * @heap: pointer to the heap struct
 * Return: pointer to the last node in the heap
*/
static binary_tree_node_t *get_last_node(const heap_t *heap)
{
	binary_tree_node_t *pos = NULL;
	size_t mask;

	/* 2^63 on a 64-bit system */
	mask = 1UL << ((sizeof(size_t) * 8) - 1);

	/* find value of most-significant bit */
	while (!(heap->size & mask))
		mask >>= 1;
	pos = heap->root;

	/* start loop from second-most significant bit */
	/* break when mask reaches 0 */
	for (mask >>= 1; mask; mask >>= 1)
	{
		/* bit is set -> right child */
		/* bit is not set -> left child */
		pos = (heap->size & mask) ? pos->right : pos->left;
	}
	return (pos);
}

/**
 * swap - swaps the data of two nodes
 * @node1: the node to swap
 * @node2: the node to be swapped
*/
static void swap(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *temp;

	temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}

/**
 * compare_values - compares to values
 * @heap: pointer to a heap struct
 * @data1: the value to compare
 * @data2: the value to be compared
 * Return: 1 if greater than, else 0
*/
static int compare_values(heap_t *heap, void *data1, void *data2)
{
	if (heap->data_cmp(data1, data2) > 0)
		return (1);
	return (0);
}

/**
 * heapify - fixes the heap after extracting a node
 * @heap: pointer to a heap struct
*/
static void heapify(heap_t *heap)
{
	binary_tree_node_t *root = heap->root;
	int swap_flag;

	if (!root->left)
		return;
	while (root->left)
	{
		swap_flag = 0;
		if (root->right && compare_values(heap, root->left->data, root->right->data))
		{
			if (compare_values(heap, root->data, root->right->data))
			{
				swap(root, root->right);
				root = root->right;
				swap_flag = 1;
			}
		}
		else
			if (compare_values(heap, root->data, root->left->data))
			{
				swap(root, root->left);
				root = root->left;
				swap_flag = 1;
			}
		if (!swap_flag)
			break;
	}
}
/**
 * heap_extract - extracts the root node of a heap
 * @heap: pointer to a heap struct
 * Return: the data from the extracted node
*/
void *heap_extract(heap_t *heap)
{
	void *return_value;
	binary_tree_node_t *last;

	return_value = heap->root->data;
	last = get_last_node(heap);
	if (last == heap->root)
	{
		heap->root = NULL;
		heap->size--;
		free(last);
		return (return_value);
	}
	heap->root->data = last->data;
	if (last == last->parent->left)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;
	free(last);
	heap->size--;
	heapify(heap);
	return (return_value);

}
