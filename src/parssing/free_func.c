/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:19:51 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 21:19:47 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	destroy_data(t_data *data, t_textures *texture)
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

// mlx_destroy_image(cub->mlx, cub->my_textures->no_texture.img);
// mlx_destroy_image(cub->mlx, cub->my_textures->so_texture.img);
// mlx_destroy_image(cub->mlx, cub->my_textures->we_texture.img);
// mlx_destroy_image(cub->mlx, cub->my_textures->ea_texture.img);
// destroy_data(cub->my_data, cub->my_textures);
// mlx_clear_window(cub->mlx, cub->win);
// mlx_destroy_image(cub->mlx, cub->img.img);
// mlx_destroy_window(cub->mlx, cub->win);
// mlx_destroy_display(cub->mlx);
// free(cub->mlx);
// free(cub->rays);
void	destroy_all(t_cub3d *cub)
{
	free(cub);
	exit(0);
}

void	free_heap(t_cub3d *cub)
{
	free(cub->my_textures->rgb);
	cub->my_textures->rgb = NULL;
	free(cub->my_textures);
	cub->my_textures = NULL;
	free(cub);
}
