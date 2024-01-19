#include "huffman.h"
#include "heap.h"


static void build_arrays(char **argv, int **freqs, char **char_array)
{
    int character, i = 0;
    FILE *file;

    file = fopen(argv[2], "r");
    character = fgetc(file);
    while (character != EOF)
    {
        freqs[character]++;
        character = fgetc(file);
    }
    fclose(file);
    while (i < CHAR_COUNT)
    {
        char_array[i] = (char)i;
        i++;
    }
}
static huffarray_t *convert_array(char *char_array, int *freqs)
{
    int i = 0, size = 0, j = 0;
    huffarray_t *huffarray = malloc(sizeof(huffarray_t));

    for (i = 0; i < CHAR_COUNT; i++)
    {
        if (freqs[i] > 0)
            size++;
    }
    huffarray->characters = malloc(sizeof(char) * size);
    huffarray->frequencies = malloc(sizeof(int) * size);
    huffarray->size = size;
    for (i = 0; i < CHAR_COUNT; i++)
    {
        if (freqs[i] > 0)
        {
            huffarray->frequencies[j] = freqs[i];
            huffarray->characters[j] = char_array[i];
            j++;
        }
    }
    return (huffarray);
}


// we need to build a hufftree, but to do that we need to build
//      two arrays, char and freq.
// these two arrays are passed to our functions from earlier
// create an array that holds freqs, use the characters as an index
// once ive built the huffman tree, we need to open a file to write to
// in that file we need to store the arrays and th
//
int huff_compression(char **argv)
{
    int frequencies[CHAR_COUNT] = {0};
    char char_array[CHAR_COUNT];
    huffarray_t *huffarray;

    build_arrays(argv, &frequencies, &char_array);
    huffarray = convert_array(&char_array, &frequencies);
    huffman_tree(huffarray);
    //
    
}