/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_texture.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:45:38 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 20:48:11 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_wall_slice(t_player *player, t_wall_render *wr)
{
	int				y;
	t_texture_calc	tc;

	tc.step = 1.0 * wr->texture_height / wr->wall_height;
	tc.tex_pos = (wr->y_start - HEIGHT / 2.0 + wr->wall_height / 2.0) * tc.step;
	y = wr->y_start;
	while (y < wr->y_end)
	{
		tc.tex_y = (int)tc.tex_pos % wr->texture_height;
		if (tc.tex_y < 0)
			tc.tex_y += wr->texture_height;
		tc.tex_pos += tc.step;
		tc.color = WALL_COLOR;
		if (wr->texture_addr && wr->texX >= 0 && wr->texX < wr->texture_width
			&& tc.tex_y >= 0 && tc.tex_y < wr->texture_height)
		{
			tc.dst = wr->texture_addr + (tc.tex_y * wr->texture_line_len
					+ wr->texX * (wr->texture_bpp / 8));
			tc.color = *(unsigned int *)tc.dst;
		}
		tc.color = darken_color(tc.color, wr->corrected_dist);
		tc.color = vignette_effect(wr->curr_x, tc.color);
		my_mlx_pixel_put(player->env, wr->curr_x, y, tc.color);
		y++;
	}
}

static int	get_texture_x(t_player *player, t_vertical_info info,
		int texture_width)
{
	double	wall_x;
	int		tex_x;

	if (info.side == SIDE_EAST || info.side == SIDE_WEST)
		wall_x = player->y + info.corrected_dist * info.rayDirY;
	else
		wall_x = player->x + info.corrected_dist * info.rayDirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texture_width);
	if ((info.side == SIDE_EAST || info.side == SIDE_WEST) && info.rayDirX > 0)
		tex_x = texture_width - tex_x - 1;
	if ((info.side == SIDE_NORTH || info.side == SIDE_SOUTH)
		&& info.rayDirY < 0)
		tex_x = texture_width - tex_x - 1;
	return (tex_x);
}

static void	get_texture_info(t_player *player, int side, t_texture_info *tex)
{
	if (side == SIDE_NORTH)
		set_north_texture(player, tex);
	else if (side == SIDE_SOUTH)
		set_south_texture(player, tex);
	else if (side == SIDE_EAST)
		set_east_texture(player, tex);
	else
		set_west_texture(player, tex);
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
