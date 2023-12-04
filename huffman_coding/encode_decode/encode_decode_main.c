#include "heap.h"
#include "huffman.h"

static int check_argv(int argc, char **argv)
{
    struct stat *sb;

    if (argc != 4 || (argv[1] != 'c' && argv[1] != 'd'))
    {
        puts("Usage: huffman <mode> <filename> <out_filename>\n");
        return(0);
    }
    
    if (stat(argv[2], &sb) != 0)
    {
        printf("No such file: %s\n", argv[2]);
        return (0);
    }
    if (stat(argv[3], &sb) == 0)
    {
        printf("File already exists: %s\n", argv[3]);
        return (0);
    }
    return (1);
}

int main(int argc, char** argv)
{
    if (check_argv(argc, argv))
    {
        if (argv[1] == 'c')
        {
            if(huff_compression())
                exit(EXIT_SUCCESS);
        }
        else
        {
            if(huff_decommpression())
                exit(EXIT_SUCCESS);
        }
    }
    exit(EXIT_FAILURE);
}