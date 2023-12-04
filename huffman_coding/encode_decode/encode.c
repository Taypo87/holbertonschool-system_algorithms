#include "huffman.h"
#include "heap.h"


static void build_arrays(char **argv, int **freqs, char **ch_array)
{
    int character, i = 0;
    FILE *file;

    file = fopen(argv[2], "r");

    character = fgetc(file);
    while(character != EOF)
    {
        freqs[character]++;
        character = fgetc(file);
    }
    while(i < CHAR_COUNT)
    {
        ch_array[i] = (char)i;
        i++;
    }
}


// we need to build a hufftree, but to do that we need to build
//      two arrays, char and freq.
// these two arrays are passed to our functions from earlier
// create and array that holds freqs, use the characters as an index
int huff_compression(char **argv)
{
    int frequencies[CHAR_COUNT] = {0};
    char char_array[CHAR_COUNT];

    build_arrays(argv, &frequencies, &char_array);
    
}