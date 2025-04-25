/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ceiling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:27:20 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/25 18:32:23 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"


typedef struct s_ceil_render
{
    double	player_dir_x;
    double	player_dir_y;
    double	plane_x;
    double	plane_y;
    int		screen_x;
    float	row_distance;
    float	floor_step_x;
    float	floor_step_y;
    float	current_ceil_x;
    float	current_ceil_y;
    int		tex_x;
    int		tex_y;
}	t_ceil_render;

static void	init_ceiling_render(t_player *player, t_ceil_render *cr)
{
    cr->player_dir_x = cos(player->dir);
    cr->player_dir_y = sin(player->dir);
    cr->plane_x = -cr->player_dir_y * tan(FOV * M_PI / 360.0);
    cr->plane_y = cr->player_dir_x * tan(FOV * M_PI / 360.0);
}

static void	calc_ceiling_position(t_player *player, t_ceil_render *cr, int y)
{
    cr->row_distance = (0.5 * HEIGHT) / (HEIGHT / 2.0 - y);
    cr->floor_step_x = cr->row_distance * (cr->player_dir_x + cr->plane_x 
        - (cr->player_dir_x - cr->plane_x)) / WIDTH;
    cr->floor_step_y = cr->row_distance * (cr->player_dir_y + cr->plane_y 
        - (cr->player_dir_y - cr->plane_y)) / WIDTH;
    cr->current_ceil_x = player->x + cr->row_distance * (cr->player_dir_x - cr->plane_x);
    cr->current_ceil_y = player->y + cr->row_distance * (cr->player_dir_y - cr->plane_y);
    cr->current_ceil_x += cr->floor_step_x * cr->screen_x;
    cr->current_ceil_y += cr->floor_step_y * cr->screen_x;
}

static int	get_ceiling_color(t_player *player, t_ceil_render *cr)
{
    int		ceil_color;
    char	*tex_pixel_ptr;

    cr->tex_x = (int)(player->env->texture->ceil_width 
        * (cr->current_ceil_x - floor(cr->current_ceil_x))) 
        & (player->env->texture->ceil_width - 1);
    cr->tex_y = (int)(player->env->texture->ceil_height 
        * (cr->current_ceil_y - floor(cr->current_ceil_y))) 
        & (player->env->texture->ceil_height - 1);
    ceil_color = CEILING_COLOR;
    if (cr->tex_x >= 0 && cr->tex_x < player->env->texture->ceil_width 
        && cr->tex_y >= 0 && cr->tex_y < player->env->texture->ceil_height)
    {
        tex_pixel_ptr = player->env->texture->ceil_addr 
            + (cr->tex_y * player->env->texture->ceil_line_len 
            + cr->tex_x * (player->env->texture->ceil_bpp / 8));
        ceil_color = *(unsigned int *)tex_pixel_ptr;
    }
    return (ceil_color);
}

void	render_ceiling(t_player *player, int screen_x, int y_start, 
                    int y_end, int wall_height)
{
    int			y;
    int			ceil_color;
    t_ceil_render	cr;

    (void) y_end;
    (void) wall_height;
    cr.screen_x = screen_x;
    init_ceiling_render(player, &cr);
    y = 0;
    while (y < y_start)
    {
        calc_ceiling_position(player, &cr, y);
        ceil_color = get_ceiling_color(player, &cr);
        my_mlx_pixel_put(player->env, screen_x, y, 
            ceil_fog_color(ceil_color, cr.row_distance));
        y++;
    }
}