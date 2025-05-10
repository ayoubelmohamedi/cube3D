/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:27:36 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 20:32:37 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_floor_render(t_player *player, t_floor_render *fr)
{
	double	fov_rad;

	fr->player_dir_x = cos(player->dir);
	fr->player_dir_y = sin(player->dir);
	fov_rad = FOV * (M_PI / 180);
	fr->plane_x = -fr->player_dir_y * tan(FOV / 2.0);
	fr->plane_y = fr->player_dir_x * tan(fov_rad / 2.0);
}

static void	calc_floor_position(t_player *player, t_floor_render *fr, int y)
{
	fr->row_distance = (0.5 * HEIGHT) / (y - HEIGHT / 2.0);
	fr->floor_step_x = fr->row_distance * (fr->player_dir_x + fr->plane_x
			- (fr->player_dir_x - fr->plane_x)) / WIDTH;
	fr->floor_step_y = fr->row_distance * (fr->player_dir_y + fr->plane_y
			- (fr->player_dir_y - fr->plane_y)) / WIDTH;
	fr->current_floor_x = player->x + fr->row_distance * (fr->player_dir_x
			- fr->plane_x);
	fr->current_floor_y = player->y + fr->row_distance * (fr->player_dir_y
			- fr->plane_y);
	fr->current_floor_x += fr->floor_step_x * fr->screen_x;
	fr->current_floor_y += fr->floor_step_y * fr->screen_x;
}

static void	get_floor_texture_coords(t_player *player, t_floor_render *fr)
{
	int	floor_width;
	int	floor_height;

	floor_width = player->env->texture->floor_width;
	floor_height = player->env->texture->floor_height;
	fr->tex_x = (int)(floor_width * (fr->current_floor_x
				- floor(fr->current_floor_x))) & (floor_width - 2);
	fr->tex_y = (int)(floor_height * (fr->current_floor_y
				- floor(fr->current_floor_y))) & (floor_height - 1);
}

static int	get_floor_color(t_player *player, t_floor_render *fr)
{
	int		floor_color;
	char	*tex_pixel_ptr;

	floor_color = FLOOR_COLOR;
	if (fr->tex_x >= 0 && fr->tex_x < player->env->texture->floor_width
		&& fr->tex_y >= 0 && fr->tex_y < player->env->texture->floor_height)
	{
		tex_pixel_ptr = player->env->texture->floor_addr + (fr->tex_y
				* player->env->texture->floor_line_len + fr->tex_x
				* (player->env->texture->floor_bpp / 8));
		floor_color = *(unsigned int *)tex_pixel_ptr;
	}
	floor_color = darken_color(floor_color, fr->row_distance);
	return (floor_color);
}

void	render_floor(t_player *player, int curr_x, int y_end)
{
	int				y;
	int				floor_color;
	t_floor_render	fr;

	fr.screen_x = curr_x;
	init_floor_render(player, &fr);
	y = y_end;
	while (y < HEIGHT)
	{
		calc_floor_position(player, &fr, y);
		get_floor_texture_coords(player, &fr);
		floor_color = get_floor_color(player, &fr);
		my_mlx_pixel_put(player->env, curr_x, y, floor_color);
		y++;
	}
}
