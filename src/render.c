/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:58:26 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/13 14:12:28 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Main render function
void	render_scene(t_env *env, t_player *player)
{
	double	fov_rad;
	double	ray_angle;
	int		x;

	fov_rad = (FOV * M_PI) / 180.0;
	if (env->img)
		mlx_destroy_image(env->mlx, env->img);
	env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
	env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
			&env->line_lenght, &env->endian);
	x = 0;
	while (x < WIDTH)
	{
		ray_angle = player->dir - (fov_rad / 2.0) + (x * fov_rad / WIDTH);
		cast_ray(player, ray_angle, x);
		x++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

void	cast_ray(t_player *player, double ray_angle, int screen_x)
{
	t_rays			rays;
	t_vertical_info	info;
	int				wall_height;

	fill_rays(&rays, player, ray_angle);
	info.rayDirX = rays.rayDirX;
	info.rayDirY = rays.rayDirY;
	if (rays.mapX < 0 || rays.mapX >= player->env->map_width || rays.mapY < 0
		|| rays.mapY >= player->env->map_height)
		return ;
	info.dist = dda_algo(&rays, &info.side, player);
	if (info.dist >= 0)
	{
		info.corrected_dist = info.dist * cos(ray_angle - player->dir);
		if (info.corrected_dist < 0.01)
			info.corrected_dist = 0.01;
		wall_height = (int)(HEIGHT / info.corrected_dist);
		fill_vertical_info(&info, screen_x, wall_height, info.corrected_dist);
		draw_vertical_line(player, info);
	}
}

void	draw_vertical_line(t_player *player, t_vertical_info info)
{
	int	y_start;
	int	y_end;

	y_start = (HEIGHT - info.wall_height) / 2;
	if (y_start < 0)
		y_start = 0;
	y_end = y_start + info.wall_height;
	if (y_end > HEIGHT)
		y_end = HEIGHT;
	render_ceiling_section(player, info.x, y_start);
	render_wall_section(player, info, y_start, y_end);
	render_floor_section(player, info.x, y_end);
}

void	my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = env->addr + (y * env->line_lenght + x * (env->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
