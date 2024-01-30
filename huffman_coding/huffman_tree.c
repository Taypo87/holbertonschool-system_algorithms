#include "huffman.h"
#include "heap.h"

/**
 * huffman_tree - builds a huffman tree fromn a priority queue
 * @data: array of characters to be stored in nodes
 * @freq: array of frequencies to be stored in nodes
 * @size: size of data and freq and tree
 * Return: pointer to the root of the huffman tree
*/
binary_tree_node_t *huffman_tree(huffarray_t *ha)
{
	heap_t *p_queue;
	binary_tree_node_t *temp;

	p_queue = huffman_priority_queue(ha->characters, ha->frequencies, ha->size);
	if (!p_queue)
		return (NULL);
	while (p_queue->size > (size_t)1)
	{
		huffman_extract_and_insert(p_queue);
	}
	temp = heap_extract(p_queue);
	heap_delete(p_queue, NULL);
	return (temp);
}
