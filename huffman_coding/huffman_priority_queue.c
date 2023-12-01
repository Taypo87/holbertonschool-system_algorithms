#include "huffman.h"
#include "heap.h"

/**
 * huff_cmp - compares two huffnodes
 * @node1: first node to be compared
 * @node2: second node to be compared to
 * Return: the difference between the two
*/
static int huff_cmp(void *node1, void *node2)
{
	binary_tree_node_t *tree1, *tree2;
	symbol_t *symbol1, *symbol2;

	tree1 = (binary_tree_node_t *)node1;
	tree2 = (binary_tree_node_t *)node2;
	symbol1 = tree1->data;
	symbol2 = tree2->data;
	return ((int)symbol1->freq - (int)symbol2->freq);
}

/**
 * huff_node_create - creates a node for a huffman tree
 * @data: character to be stored in a symbol
 * @freq: the frequency of the stored character
 * Return: pointer to the newly created node
*/
static binary_tree_node_t *huff_node_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = symbol_create(data, freq);
	return (binary_tree_node(NULL, symbol));
}

/**
 * huffman_priority_queue - creates a priority queue (min heap)
 * @data: array of characters to be added to the queue
 * @freq: the associated frequency of data characters
 * @size: size of the data and freq array
 * Return: pointer to the priority queue
*/
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *pqueue;
	binary_tree_node_t *node;
	size_t i;

	pqueue = heap_create(huff_cmp);

	for (i = 0; i < size; i++)
	{
		node = huff_node_create(data[i], freq[i]);
		heap_insert(pqueue, node);
	}
	return (pqueue);
}
