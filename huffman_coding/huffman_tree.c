#include "huffman.h"
#include "heap.h"

/**
 * huffman_tree - builds a huffman tree fromn a priority queue
 * @data: array of characters to be stored in nodes
 * @freq: array of frequencies to be stored in nodes
 * Return: pointer to the root of the huffman tree
*/
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	heap_t *p_queue;

	p_queue = huffman_priority_queue(data, freq, size);
	while (size != 1)
	{
		huffman_extract_and_insert(p_queue);
	}
	return (p_queue->root);
}
