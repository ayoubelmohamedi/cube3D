/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:47:24 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 23:01:31 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_rays(t_rays *rays, t_player *player, double ray_angle)
{
	rays->rayX = &player->x;
	rays->rayY = &player->y;
	rays->rayDirX = cos(ray_angle);
	rays->rayDirY = sin(ray_angle);
	rays->mapX = (int)*rays->rayX;
	rays->mapY = (int)*rays->rayY;
}

void	fill_vertical_info(t_vertical_info *info, int screen_x, int wall_height,
		double correct_dist)
{
	info->x = screen_x;
	info->wall_height = wall_height;
	info->corrected_dist = correct_dist;
}

void	render_ceiling_section(t_player *player, int x, int y_start)
{
	int	y;

	y = 0;
	while (y < y_start)
	{
		my_mlx_pixel_put(player->env, x, y, player->env->c_color);
		y++;
	}
}

void	render_wall_section(t_player *player, t_vertical_info info, int y_start,
		int y_end)
{
	int	y;

	y = y_start;
	if (player->env->has_wall_texture)
		render_wall_tex(player, y_start, y_end, info);
	else
    {
		while (y < y_end)
		{
			my_mlx_pixel_put(player->env, info.x, y, vignette_effect(info.x,
					WALL_COLOR));
			y++;
		}
    }
}

void	render_floor_section(t_player *player, int x, int y_end)
{
	int	y;

	y = y_end;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(player->env, x, y, player->env->f_color);
		y++;
	}

}	
    