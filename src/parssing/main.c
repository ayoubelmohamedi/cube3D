#include "parsing.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Error: Usage: %s <map_file.cub>\n", argv[0]);
        return (1);
    }
    
    t_data data;
    t_cub *cub = malloc(sizeof(t_cub));
    t_texture *texture = malloc(sizeof(t_texture));
    
    if (!cub || !texture)
    {
        printf("Error: Memory allocation failed\n");
        return (1);
    }
    
    if (proccess_input(&data, cub, argv[1], texture))
    {
        printf("Error during map processing\n");
        free_heap(cub);
        return (1);
    }

    return (0);
}