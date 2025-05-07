/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:11:50 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:12:02 by aez-zoui         ###   ########.fr       */
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

void	ft_freemap(t_maplist **map)
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

void	destroy_data(t_data *data, t_wall_textures *texture)
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
