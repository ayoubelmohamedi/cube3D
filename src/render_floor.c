/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:27:36 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/25 18:32:34 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

typedef struct s_floor_render
{
    double	player_dir_x;
    double	player_dir_y;
    double	plane_x;
    double	plane_y;
    int		screen_x;
    double	row_distance;
    float	floor_step_x;
    float	floor_step_y;
    float	current_floor_x;
    float	current_floor_y;
    int		tex_x;
    int		tex_y;
}	t_floor_render;

static void	init_floor_render(t_player *player, t_floor_render *fr)
{
    fr->player_dir_x = cos(player->dir);
    fr->player_dir_y = sin(player->dir);
    double	fov_rad = FOV * (M_PI / 180);
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
    fr->current_floor_x = player->x + fr->row_distance 
        * (fr->player_dir_x - fr->plane_x);
    fr->current_floor_y = player->y + fr->row_distance 
        * (fr->player_dir_y - fr->plane_y);
    fr->current_floor_x += fr->floor_step_x * fr->screen_x;
    fr->current_floor_y += fr->floor_step_y * fr->screen_x;
}

static void	get_floor_texture_coords(t_player *player, t_floor_render *fr)
{
    fr->tex_x = (int)(player->env->texture->floor_width 
        * (fr->current_floor_x - floor(fr->current_floor_x))) 
        & (player->env->texture->floor_width - 2);
    fr->tex_y = (int)(player->env->texture->floor_height 
        * (fr->current_floor_y - floor(fr->current_floor_y))) 
        & (player->env->texture->floor_height - 1);
}

static int	get_floor_color(t_player *player, t_floor_render *fr)
{
    int		floor_color;
    char	*tex_pixel_ptr;

    floor_color = FLOOR_COLOR;
    if (fr->tex_x >= 0 && fr->tex_x < player->env->texture->floor_width 
        && fr->tex_y >= 0 && fr->tex_y < player->env->texture->floor_height)
    {
        tex_pixel_ptr = player->env->texture->floor_addr 
            + (fr->tex_y * player->env->texture->floor_line_len 
            + fr->tex_x * (player->env->texture->floor_bpp / 8));
        floor_color = *(unsigned int *)tex_pixel_ptr;
    }
    floor_color = darken_color(floor_color, fr->row_distance);
    return (floor_color);
}

void	render_floor(t_player *player, int screen_x, int y_start, 
                    int y_end, int wall_height)
{
    int				y;
    int				floor_color;
    t_floor_render	fr;

    (void)y_start;
    (void)wall_height;
    fr.screen_x = screen_x;
    init_floor_render(player, &fr);
    y = y_end;
    while (y < HEIGHT)
    {
        calc_floor_position(player, &fr, y);
        get_floor_texture_coords(player, &fr);
        floor_color = get_floor_color(player, &fr);
        my_mlx_pixel_put(player->env, screen_x, y, floor_color);
        y++;
    }
}