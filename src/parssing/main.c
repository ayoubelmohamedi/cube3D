#include "parsing.h"


int main(int argc, char **argv)
{
    t_cub3d *cub;
    t_textures *textures;
    t_data my_data;

    if (argc != 2)
    {
        printf("Invalid argm\n");
        return (1);
    }
    cub = malloc(sizeof(t_cub3d));
    if (!cub)
        return (1);
    textures = malloc(sizeof(textures));
    if (!textures){
        free(cub);
        return (1);
    }
    printf("Here \n");
    if (parrsing_input(cub, &my_data, textures, argv[1]))
    {
        free(cub);
        free(textures);
        return (0);
    }
    //start_prg(cub, textures);
    return (0);
}