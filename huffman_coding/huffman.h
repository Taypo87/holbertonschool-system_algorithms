#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <stdio.h>
#include <stdlib.h>

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

symbol_t *symbol_create(char data, size_t freq);

#endif