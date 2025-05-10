/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efffects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbookpro <macbookpro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:00 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 17:39:28 by macbookpro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Choose wall color by type Red, Green, Blue
int	get_color(int wall_type)
{
	if (wall_type == 1)
		return (0xFF0000);
	if (wall_type == 2)
		return (0x00FF00);
	if (wall_type == 3)
		return (0x0000FF);
	return (0xAAAAAA);
}

// Darken the color based on distance
int	darken_color(int color, double dist)
{
	t_rgb	rgb;

	double factor = 1.0 / (1.0 + dist * 0.05); // fade with distance
	rgb.r = ((color >> 16) & 0xFF) * factor;
	rgb.g = ((color >> 8) & 0xFF) * factor;
	rgb.b = (color & 0xFF) * factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	ceil_fog_color(int ceil_color, int rowDistance)
{
	double	fog_factor;
	t_rgb	rgb;

	fog_factor = 1.0 - exp(-rowDistance * FOG_DENSITY);
	if (fog_factor < 0.0)
		fog_factor = 0.0;
	if (fog_factor > 1.0)
		fog_factor = 1.0;
	rgb.ceil_r = (ceil_color >> 16) & 0xFF;
	rgb.ceil_g = (ceil_color >> 8) & 0xFF;
	rgb.ceil_b = ceil_color & 0xFF;
	rgb.fog_r = (FOG_COLOR >> 16) & 0xFF;
	rgb.fog_g = (FOG_COLOR >> 8) & 0xFF;
	rgb.fog_b = FOG_COLOR & 0xFF;
	rgb.final_r = (int)(rgb.ceil_r * (1.0 - fog_factor) + rgb.fog_r
			* fog_factor);
	rgb.final_g = (int)(rgb.ceil_g * (1.0 - fog_factor) + rgb.fog_g
			* fog_factor);
	rgb.final_b = (int)(rgb.ceil_b * (1.0 - fog_factor) + rgb.fog_b
			* fog_factor);
	return ((rgb.final_r << 16) | (rgb.final_g << 8) | rgb.final_b);
}

int	vignette_effect(int curr_x, int color)
{
	double	vignette_strength;
	double	dist_from_center;
	double	vignette_factor;
	int		r;
	int		g;
	int		b;

	vignette_strength = 0.4;
	dist_from_center = fabs((double)curr_x - WIDTH / 2.0) / (WIDTH / 2.0);
	vignette_factor = 1.0 - dist_from_center * vignette_strength;
	if (vignette_factor < 0.0)
		vignette_factor = 0.0;
	r = ((color >> 16) & 0xFF) * vignette_factor;
	g = ((color >> 8) & 0xFF) * vignette_factor;
	b = (color & 0xFF) * vignette_factor;
	return ((r << 16) | (g << 8) | b);
}
