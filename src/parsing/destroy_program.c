#include "parsing.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_mapclear(t_maplist **map)
{
	t_maplist	*tmp;

	if (!map || !*map)
		return ;
	while (*map)
	{
		tmp = *map;
		*map = (*map)->next;
		free(tmp->line);
		free(tmp);
	}
	*map = NULL;
}

void	destroy_data(t_data *data, t_texture *texture)
{
	free(texture->rgb->f);
	free(texture->rgb->c);
	free(texture->rgb);
	free(texture->no);
	free(texture->so);
	free(texture->we);
	free(texture->ea);
	free(texture);
	free_array(data->map);
	data->map = NULL;
}

void	destroy_all(t_cub *cub)
{
	destroy_data(cub->data, cub->texture);
	free(cub);
	exit(0);
}

void	free_heap(t_cub *cub)
{
	free(cub->texture->rgb);
	cub->texture->rgb = NULL;
	free(cub->texture);
	cub->texture = NULL;
	free(cub);
}
