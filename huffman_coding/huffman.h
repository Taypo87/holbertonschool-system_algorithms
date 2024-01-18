#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <stdio.h>
#include <stdlib.h>
#include <heap.h>
#include <strings.h>
#include <sys/stat.h>

#define CHAR_COUNT 256
/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
    char data;
    size_t freq;
} symbol_t;

typedef struct huffarray_s
{
    char *characters;
    int *frequencies;
    int size;
} huffarray_t;



symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);
int huffman_codes(char *data, size_t *freq, size_t size);
int huff_compression(char **argv);
int huff_decompression(char **argv);
#endif