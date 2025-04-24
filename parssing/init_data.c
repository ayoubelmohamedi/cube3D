#include "cub3d.h"

int    init_texture(t_textures *my_texts)
{
    my_texts->so = NULL;
    my_texts->ea = NULL;
    my_texts->so = NULL;
    my_texts->we = NULL;
    my_texts->rgb = malloc(sizeof(t_rgb));
    if(!my_texts->rgb)
    {
        return (1);
    }
    my_texts->no_texture.img = NULL;
    my_texts->ea_texture.img = NULL;
    my_texts->we_texture.img = NULL;
    my_texts->so_texture.img = NULL;
    my_texts->rgb->c = NULL;
    my_texts->rgb->f = NULL;

    return (0);
}


int	init_data(t_data *data)
{
	data->map = NULL;
	data->col = 0;
	data->row = 0;
	data->j = 0;
	data->i = 0;
	return (0);
}

int init_cub(t_cub3d *cub, t_data *my_data, t_textures *my_textures)
{
    cub->my_data = my_data;
    cub->my_textures = my_textures;
    return (0);
}