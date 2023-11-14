#include <stdlib.h>
#include <stdio.h>
#include "rb_trees.h"

void rb_tree_print(const rb_tree_t *tree);

/**
 * main - Entry point
 *
 * Return: 0 on success
 */
int main(void)
{
	rb_tree_t *root;
	rb_tree_t *node;

	root = NULL;
	node = rb_tree_insert(&root, 43);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 34);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 65);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);
	node = rb_tree_insert(&root, 13);
	printf("Inserted: %d\n", node->n);
	rb_tree_print(root);

	return (0);
}
