#include "huffman.h"

/**
 * symbol_create - initializes a new symbol struct
 * @data: the data to be stored in the symbol struct
 * @freq: the frequency at which the data appears
 * Return: pointer to the newly allocated symbol
*/
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol = calloc(1, sizeof(symbol_t));

	if (!symbol)
		return (NULL);
	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
