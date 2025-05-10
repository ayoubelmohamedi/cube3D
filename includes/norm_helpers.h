/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 22:33:27 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 23:04:07 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef NORM_HELPERS_H
#define NORM_HELPERS_H

typedef struct s_dda
{
	int		side_hit;
	int		stepX;
	int		stepY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
}			t_dda;
typedef struct s_rays
{
    double rayDirX;
    double rayDirY;
    double *rayX;
    double *rayY;
    int 	mapX;
    int 	mapY;
} t_rays;


typedef struct s_vertical_info
{
    int x;
    int wall_height;
    double corrected_dist;
    int side;
    double rayDirX;
    double rayDirY;
    double dist;
} t_vertical_info;

typedef struct s_rgb_info
{
	int	r;
	int	g;
	int	b;
	int	ceil_r;
	int	ceil_g;
	int	ceil_b;
	int	fog_r;
	int	fog_g;
	int	fog_b;
	int	final_r;
	int	final_g;
	int	final_b;
}		t_rgb_info;

typedef struct s_texture_info {
    char	*addr;
    int		width;
    int		height;
    int		bpp;
    int		line_len;
}	t_texture_info;

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

typedef struct s_texture_calc {
    int     tex_y;
    double  step;
    double  tex_pos;
    char    *dst;
    int     color;
}   t_texture_calc;



#endif