/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   efffects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:00 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 23:03:33 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Darken the color based on distance fade with distance
int	darken_color(int color, double dist)
{
	t_rgb_info	rgb;
	double		factor;

	factor = 1.0 / (1.0 + dist * 0.05);
	rgb.r = ((color >> 16) & 0xFF) * factor;
	rgb.g = ((color >> 8) & 0xFF) * factor;
	rgb.b = (color & 0xFF) * factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}

int	vignette_effect(int curr_x, int color)
{
	double		vignette_strength;
	double		dist_from_center;
	double		vignette_factor;
	t_rgb_info	rgb;

	vignette_strength = 0.4;
	dist_from_center = fabs((double)curr_x - WIDTH / 2.0) / (WIDTH / 2.0);
	vignette_factor = 1.0 - dist_from_center * vignette_strength;
	if (vignette_factor < 0.0)
		vignette_factor = 0.0;
	rgb.r = ((color >> 16) & 0xFF) * vignette_factor;
	rgb.g = ((color >> 8) & 0xFF) * vignette_factor;
	rgb.b = (color & 0xFF) * vignette_factor;
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
