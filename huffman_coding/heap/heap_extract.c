#include "heap.h"

/**
 * get_last_node - finds the location of the last node in a heap
 * @heap: pointer to the heap struct
 * Return: pointer to the last node in the heap
*/
binary_tree_node_t *get_last_node(const heap_t *heap)
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
static binary_tree_node_t *min_child(binary_tree_node_t *node, int (*compare_values)(void *, void *))
{	int result;

	if (!node)
		return (NULL);
	if (!node->right)
		return (node->left);
	result = compare_values(node->left->data, node->right->data);
	if (result <= 0)
		return(node->left);
	else
		return(node->right);
}
/**
 * heapify - fixes the heap after extracting a node
 * @heap: pointer to a heap struct
*/
void heapify(heap_t *heap)
{
	binary_tree_node_t *pos, *child;
	void *temp;

	pos = heap->root;
	child = min_child(pos, compare_values(heap, pos->left->data, pos->right->data));

	while (child && (heap->data_cmp(pos, child) >= 0))
	{
		swap(pos, child);
		pos = child;
		child = min_child(pos, compare_values);
	}

}
/**
 * heap_extract - extracts the root node of a heap
 * @heap: pointer to a heap struct
 * Return: the data from the extracted node
*/
void *heap_extract(heap_t *heap)
{
	void *rv;
	binary_tree_node_t *last;

	rv = heap->root->data;
	last = get_last_node(heap);
	if (last == heap->root)
	{
		heap->root = NULL;
		heap->size--;
		free(last);
		return (rv);
	}
	heap->root->data = last->data;
	if (last == last->parent->left)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;
	free(last);
	heap->size--;
	heapify(heap);
	return (rv);

}
