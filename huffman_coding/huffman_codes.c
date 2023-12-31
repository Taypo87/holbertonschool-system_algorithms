#include "heap.h"
#include "huffman.h"

/**
 * deleter - recursive function that frees data and nodes of a heap
 * @node: the current node to free
 * @free_data: function that frees the data in a heap node
*/
static void deleter(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;
	deleter(node->left, free_data);
	deleter(node->right, free_data);
	if (free_data)
		free_data(node->data);
	free(node);

}
/**
 * huff_delete - deletes a heap
 * @hufftree: pointer to a heap struct
 * @free_data: function pointer that frees a nodes stored data
*/
static void huff_delete(binary_tree_node_t *hufftree,
								 void (*free_data)(void *))
{
	deleter(hufftree, free_data);
}


/**
 * huff_codes - generates coding from a huffman tree
 * @root: the root of a huffman tree
 * @code: pointer to the code being generated
 * @depth: the index of each code character
*/
static void huff_codes(binary_tree_node_t *root, char *code, int depth)
{

	if (root->left == NULL && root->right == NULL)
	{
		code[depth] = '\0';
		printf("%s: %s\n", (char *)root->data, code);
		return;
	}
	if (root->left != NULL)
	{
		code[depth] = '0';
		huff_codes(root->left, code, depth + 1);
	}
	if (root->right != NULL)
	{
		code[depth] = '1';
		huff_codes(root->right, code, depth + 1);
	}
}
/**
 * huffman_codes - gets the code associated with each character
 * @data: pointer to an array of characters
 * @freq: the frequenciy of the associated character
 * @size: size of data and freq arrays
 * Return: 1 on success, else 0
*/
int huffman_codes(char *data, size_t *freq, size_t size)
{
	char codes[64];
	int depth = 0;
	binary_tree_node_t *hufftree;

	hufftree = huffman_tree(data, freq, size);
	if (!hufftree)
		return (0);
	huff_codes(hufftree, codes, depth);
	huff_delete(hufftree, free);
	return (1);
}
