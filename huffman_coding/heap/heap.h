#ifndef _HEAP_
#define _HEAP_

#include <stdio.h>
#include <stdlib.h>

/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

typedef struct queue_s
{
	binary_tree_node_t *node;
	struct queue_s *next;
	struct queue_s *prev;
} queue_t;

binary_tree_node_t *node_swap(binary_tree_node_t *parent, binary_tree_node_t *node);
binary_tree_node_t *value_check(heap_t *heap, binary_tree_node_t *node);
heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
void *heap_extract(heap_t *heap);
void heap_delete(heap_t *heap, void (*free_data)(void *));
void heapify(heap_t *heap);
binary_tree_node_t *get_last_node(const heap_t *heap);

#endif
