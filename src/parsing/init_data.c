/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:13:29 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:13:31 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	init_data(t_data *data)
{
	data->map = NULL;
	data->col = 0;
	data->row = 0;
	data->j = 0;
	data->i = 0;
	return (0);
}

int	init_cub(t_cub *cub, t_data *data, t_wall_textures *texture)
{
	cub->data = data;
	cub->player_x = 0;
	cub->player_y = 0;
	cub->texture = texture;;
	return (0);
}

int	init_texture(t_wall_textures *texture)
{
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->ea = NULL;
	texture->rgb = malloc(sizeof(t_rgb));
	if (!texture->rgb)
	{
		return (1);
	}
	texture->rgb->f = NULL;
	texture->rgb->c = NULL;
	return (0);
}

int	ft_exit(t_cub *cub)
{
	destroy_all(cub);
	exit(0);
	return (0);
}

