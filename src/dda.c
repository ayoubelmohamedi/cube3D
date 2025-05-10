/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:55:54 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 20:11:03 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_dda(t_rays *rays, t_dda *dda)
{
	rays->mapX = (int)*rays->rayX;
	rays->mapY = (int)*rays->rayY;
	dda->deltaDistX = fabs(1 / rays->rayDirX);
	dda->deltaDistY = fabs(1 / rays->rayDirY);
	dda->stepX = 1;
	if (rays->rayDirX < 0)
		dda->stepX = -1;
	dda->stepY = 1;
	if (rays->rayDirY < 0)
		dda->stepY = -1;
	if (rays->rayDirX < 0)
		dda->sideDistX = (*rays->rayX - rays->mapX) * dda->deltaDistX;
	else
		dda->sideDistX = (rays->mapX + 1.0 - *rays->rayX) * dda->deltaDistX;
	if (rays->rayDirY < 0)
		dda->sideDistY = (*rays->rayY - rays->mapY) * dda->deltaDistY;
	else
		dda->sideDistY = (rays->mapY + 1.0 - *rays->rayY) * dda->deltaDistY;
	dda->side_hit = 0;
}

static int	perform_dda(int *mapX, int *mapY, t_dda *dda, t_player *player)
{
	if (dda->sideDistX < dda->sideDistY)
	{
		dda->sideDistX += dda->deltaDistX;
		*mapX += dda->stepX;
		dda->side_hit = 0;
	}
	else
	{
		dda->sideDistY += dda->deltaDistY;
		*mapY += dda->stepY;
		dda->side_hit = 1;
	}
	if (*mapX < 0 || *mapX >= player->env->map_width || *mapY < 0
		|| *mapY >= player->env->map_height)
		return (-1);
	if ((player->env->map[*mapY][*mapX]) != '0')
		return (1);
	return (0);
}

static double	calculate_wall_distance(t_rays *rays, int *side, t_dda *dda)
{
	if (dda->side_hit == 0)
	{
		*side = SIDE_EAST;
		if (rays->rayDirX > 0)
			*side = SIDE_WEST;
		return (dda->sideDistX - dda->deltaDistX);
	}
	else
	{
		*side = SIDE_SOUTH;
		if (rays->rayDirY > 0)
			*side = SIDE_NORTH;
		return (dda->sideDistY - dda->deltaDistY);
	}
}

double	dda_algo(t_rays *rays, int *side, t_player *player)
{
	t_dda	dda;
	int		result;

	init_dda(rays, &dda);
	while (1)
	{
		result = perform_dda(&rays->mapX, &rays->mapY, &dda, player);
		if (result == -1)
			return (-1.0);
		if (result == 1)
			break ;
	}
	return (calculate_wall_distance(rays, side, &dda));
}
