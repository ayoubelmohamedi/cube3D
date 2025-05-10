/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:27:46 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 19:46:35 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}			t_wall_render;

static void	draw_wall_slice(t_player *player, t_wall_render *wr)
{
	int		y;
	int		texY;
	int		color;
	char	*dst;
	double	step;
	double	texPos;

	step = 1.0 * wr->texture_height / wr->wall_height;
	texPos = (wr->y_start - HEIGHT / 2.0 + wr->wall_height / 2.0) * step;
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
			dst = wr->texture_addr + (texY * wr->texture_line_len + wr->texX
					* (wr->texture_bpp / 8));
			color = *(unsigned int *)dst;
		}
		color = darken_color(color, wr->corrected_dist);
		color = vignette_effect(wr->curr_x, color);
		my_mlx_pixel_put(player->env, wr->curr_x, y, color);
		y++;
	}
}

static int	get_texture_x(t_player *player, t_vertical_info info,
		int texture_width)
{
	double	wallX;
	int		texX;

	if (info.side == SIDE_EAST || info.side == SIDE_WEST)
		wallX = player->y + info.corrected_dist * info.rayDirY;
	else
		wallX = player->x + info.corrected_dist * info.rayDirX;
	wallX -= floor(wallX);
	texX = (int)(wallX * (double)texture_width);
	if ((info.side == SIDE_EAST || info.side == SIDE_WEST) && info.rayDirX > 0)
		texX = texture_width - texX - 1;
	if ((info.side == SIDE_NORTH || info.side == SIDE_SOUTH)
		&& info.rayDirY < 0)
		texX = texture_width - texX - 1;
	return (texX);
}

static void	get_texture_info(t_player *player, int side, t_texture_info *tex)
{
	if (side == SIDE_NORTH)
	{
		tex->addr = player->env->walls->north_addr;
		tex->width = player->env->walls->north_width;
		tex->height = player->env->walls->north_height;
		tex->bpp = player->env->walls->north_bpp;
		tex->line_len = player->env->walls->north_line_len;
	}
	else if (side == SIDE_SOUTH)
	{
		tex->addr = player->env->walls->south_addr;
		tex->width = player->env->walls->south_width;
		tex->height = player->env->walls->south_heght;
		tex->bpp = player->env->walls->south_bpp;
		tex->line_len = player->env->walls->south_line_len;
	}
	else if (side == SIDE_EAST)
	{
		tex->addr = player->env->walls->east_addr;
		tex->width = player->env->walls->east_width;
		tex->height = player->env->walls->east_height;
		tex->bpp = player->env->walls->east_bpp;
		tex->line_len = player->env->walls->east_line_len;
	}
	else
	{
		tex->addr = player->env->walls->west_addr;
		tex->width = player->env->walls->west_width;
		tex->height = player->env->walls->west_height;
		tex->bpp = player->env->walls->west_bpp;
		tex->line_len = player->env->walls->west_line_len;
	}
}

// Main wall texture rendering function
void	render_wall_tex(t_player *player, int y_start, int y_end,
		t_vertical_info info)
{
	t_wall_render	wr;
	t_texture_info	tex;

	wr.y_start = y_start;
	wr.y_end = y_end;
	wr.curr_x = info.x;
	wr.corrected_dist = info.corrected_dist;
	wr.wall_height = info.wall_height;
	get_texture_info(player, info.side, &tex);
	wr.texture_addr = tex.addr;
	wr.texture_width = tex.width;
	wr.texture_height = tex.height;
	wr.texture_bpp = tex.bpp;
	wr.texture_line_len = tex.line_len;
	wr.texX = get_texture_x(player, info, wr.texture_width);
	draw_wall_slice(player, &wr);
}
