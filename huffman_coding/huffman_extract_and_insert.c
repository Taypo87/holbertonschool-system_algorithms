#include "huffman.h"
#include "heap.h"

/**
 * huffman_extract_and_insert - extracts 2 nodes
 *             inserts one with them as children
 * @priority_queue: the queue to operate on
 * Return: 1 on success, else 0
*/
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *new_node, *node1, *node2;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t newfreq;

	if (!priority_queue)
		return (0);

	node1 = heap_extract(priority_queue);
	symbol1 = (symbol_t *)node1->data;
	node2 = heap_extract(priority_queue);
	symbol2 = (symbol_t *)node2->data;
	newfreq = symbol1->freq + symbol2->freq;
	new_symbol = symbol_create(-1, newfreq);
	new_node = binary_tree_node(NULL, new_symbol);
	new_node->right = node1;
	node1->parent = new_node;
	new_node->left = node2;
	node2->parent = new_node;
	heap_insert(priority_queue, new_node);

	return (1);
}
