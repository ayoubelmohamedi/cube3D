/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:59:38 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/10 14:59:43 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static double	get_player_angle(char dir)
{
	if (dir == 'N')
		return (3 * MM_PI / 2);
	if (dir == 'S')
		return (MM_PI / 2);
	if (dir == 'E')
		return (0);
	return (MM_PI);
}

void	fill_player_pos_dir(t_cub *cub)
{
	int		i;
	int		j;
	char	cell;

	i = -1;
	while (++i < cub->data->row)
	{
		j = -1;
		while (++j < cub->data->col)
		{
			cell = cub->data->map[i][j];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
			{
				cub->player_x = j + 0.5;
				cub->player_y = i + 0.5;
				cub->p_angle = get_player_angle(cell);
				cub->data->map[i][j] = '0';
				cub->data->i = i;
				cub->data->j = j;
				return ;
			}
		}
	}
	printf("Error: No player position found in map\n");
}

int	check_player(t_cub *cub)
{
	int		i;
	int		j;
	char	cell;
	int		countp;

	i = -1;
	countp = 0;
	while (++i < cub->data->row)
	{
		j = -1;
		while (++j < cub->data->col)
		{
			cell = cub->data->map[i][j];
			if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				countp++;
		}
	}
	if (countp != 1)
		return (1);
	else
		return (0);
}

int	start_parser(t_cub *cub, t_data *data, char *path, int fd)
{
	if (!check_extension(path, "cub"))
	{
		printf("Error in Extension\n");
		return (1);
	}
	if (valid_texture(cub, cub->texture, fd))
		return (1);
	if (check_map(data, path))
	{
		printf("Invalid Map\n");
		return (1);
	}
	if (check_player(cub))
	{
		printf("player position not found\n");
		return (1);
	}
	fill_player_pos_dir(cub);
	return (0);
}

int	proccess_input(t_data *data, t_cub *cub, char *path,
	t_wall_textures *texture)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error in The file");
		(free(cub), free(texture));
		exit(1);
	}
	if (init_data(data))
		return (close(fd), 1);
	if (init_texture(texture))
		return (close(fd), 1);
	if (init_cub(cub, data, texture))
		return (close(fd), 1);
	if (start_parser(cub, data, path, fd))
	{
		destroy_data(cub->data, cub->texture);
		(free(cub), close(fd));
		exit(1);
	}
	close(fd);
	return (0);
}
