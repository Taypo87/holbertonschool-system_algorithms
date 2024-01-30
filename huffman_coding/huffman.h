#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <stdio.h>
#include <stdlib.h>
#include <heap.h>
#include <strings.h>
#include <sys/stat.h>

#define CHAR_COUNT 256
#define CODE_MAX 32
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
    huffcodes_t *code_array;
    int size;
} huffarray_t;

typedef struct huffcodes_s
{
    char character;
    char code[CODE_MAX];
} huffcodes_t;



symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(huffarray_t *ha);
int huffman_codes(huffarray_t *ha);
int huff_compression(char **argv);
int huff_decompression(char **argv);
#endif