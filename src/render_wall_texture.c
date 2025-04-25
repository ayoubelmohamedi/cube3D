/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:27:46 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/25 18:15:45 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


typedef struct s_wall_render
{
    int		y_start;
    int		y_end;
    int		curr_x;
    int		corrected_dist;
    int		wall_height;
    char	*texture_addr;
    int		texture_width;
    int		texture_height;
    int		texture_bpp;
    int		texture_line_len;
    int		texX;
}	t_wall_render;


static void	draw_wall_slice(t_player *player, t_wall_render *wr)
{
    int		y;
    int		texY;
    int		color;
    char	*dst;

    double step = 1.0 * wr->texture_height / wr->wall_height;
    double texPos = (wr->y_start - HEIGHT / 2.0 + wr->wall_height / 2.0) * step;
    
    y = wr->y_start;
    while (y < wr->y_end)
    {
        texY = (int)texPos % wr->texture_height;
        if (texY < 0)
            texY += wr->texture_height;
        texPos += step;
        color = WALL_COLOR;
        if (wr->texture_addr && wr->texX >= 0 && wr->texX < wr->texture_width
            && texY >= 0 && texY < wr->texture_height)
        {
            dst = wr->texture_addr + (texY * wr->texture_line_len 
                    + wr->texX * (wr->texture_bpp / 8));
            color = *(unsigned int *)dst;
        }
        color = darken_color(color, wr->corrected_dist);
        color = vignette_effect(wr->curr_x, color);
        my_mlx_pixel_put(player->env, wr->curr_x, y, color);
        y++;
    }
}

static int	get_texture_x(t_player *player, int side, double corrected_dist,
    int rayDirX, int rayDirY, int texture_width)
{
    double	wallX;
    int		texX;
    
    if (side == SIDE_EAST || side == SIDE_WEST)
        wallX = player->y + corrected_dist * rayDirY;
    else
        wallX = player->x + corrected_dist * rayDirX;
    wallX -= floor(wallX);
    texX = (int)(wallX * (double)texture_width);
    if ((side == SIDE_EAST || side == SIDE_WEST) && rayDirX > 0)
        texX = texture_width - texX - 1;
    if ((side == SIDE_NORTH || side == SIDE_SOUTH) && rayDirY < 0)
        texX = texture_width - texX - 1;
    return (texX);
}

static void	get_texture_info(t_player *player, int side, char **texture_addr, 
    int *texture_width, int *texture_height, 
    int *texture_bpp, int *texture_line_len)
{
    if (side == SIDE_NORTH)
    {
        *texture_addr = player->env->walls->north_addr;
        *texture_width = player->env->walls->north_width;
        *texture_height = player->env->walls->north_height;
        *texture_bpp = player->env->walls->north_bpp;
        *texture_line_len = player->env->walls->north_line_len;
    }
    else if (side == SIDE_SOUTH)
    {
        *texture_addr = player->env->walls->south_addr;
        *texture_width = player->env->walls->south_width;
        *texture_height = player->env->walls->south_heght; 
        *texture_bpp = player->env->walls->south_bpp;
        *texture_line_len = player->env->walls->south_line_len;
    }
    else if (side == SIDE_EAST)
    {
        *texture_addr = player->env->walls->east_addr;
        *texture_width = player->env->walls->east_width;
        *texture_height = player->env->walls->east_height;
        *texture_bpp = player->env->walls->east_bpp;
        *texture_line_len = player->env->walls->east_line_len;
    }
    else
    {
        *texture_addr = player->env->walls->west_addr;
        *texture_width = player->env->walls->west_width;
        *texture_height = player->env->walls->west_height;
        *texture_bpp = player->env->walls->west_bpp;
        *texture_line_len = player->env->walls->west_line_len;
    }
}

// Main wall texture rendering function
void	render_wall_tex(t_player *player, int y_start, int y_end, int curr_x,
    int corrected_dist, int rayDirX, int rayDirY, int side, 
    int wall_height)
{
    t_wall_render	wr;

    wr.y_start = y_start;
    wr.y_end = y_end;
    wr.curr_x = curr_x;
    wr.corrected_dist = corrected_dist;
    wr.wall_height = wall_height;
    
    get_texture_info(player, side, &wr.texture_addr, &wr.texture_width, 
        &wr.texture_height, &wr.texture_bpp, &wr.texture_line_len);
    
    wr.texX = get_texture_x(player, side, corrected_dist, rayDirX, rayDirY, 
            wr.texture_width);
    
    draw_wall_slice(player, &wr);
}

