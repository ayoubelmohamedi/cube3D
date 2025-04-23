/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:00 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/23 08:56:01 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// Choose wall color by type
int get_color(int wall_type)
{
    if (wall_type == 1)
        return 0xFF0000; // Red
    if (wall_type == 2)
        return 0x00FF00; // Green
    if (wall_type == 3)
        return 0x0000FF; // Blue
    return 0xAAAAAA;
}

// Darken the color based on distance
int darken_color(int color, double dist)
{
    double factor = 1.0 / (1.0 + dist * 0.05); // fade with distance
    int r = ((color >> 16) & 0xFF) * factor;
    int g = ((color >> 8) & 0xFF) * factor;
    int b = (color & 0xFF) * factor;
    return (r << 16) | (g << 8) | b;
}

int ceil_fog_color(int ceil_color, int rowDistance)
{
    double fog_factor = 1.0 - exp(-rowDistance * FOG_DENSITY);
    if (fog_factor < 0.0) fog_factor = 0.0;
    if (fog_factor > 1.0) fog_factor = 1.0;

    int ceil_r = (ceil_color >> 16) & 0xFF;
    int ceil_g = (ceil_color >> 8) & 0xFF;
    int ceil_b = ceil_color & 0xFF;

    int fog_r = (FOG_COLOR >> 16) & 0xFF;
    int fog_g = (FOG_COLOR >> 8) & 0xFF;
    int fog_b = FOG_COLOR & 0xFF;

    int final_r = (int)(ceil_r * (1.0 - fog_factor) + fog_r * fog_factor);
    int final_g = (int)(ceil_g * (1.0 - fog_factor) + fog_g * fog_factor);
    int final_b = (int)(ceil_b * (1.0 - fog_factor) + fog_b * fog_factor);

    return ((final_r << 16) | (final_g << 8) | final_b);
}

int vignette_effect(int curr_x, int color)
{
    double vignette_strength = 0.4;
    double dist_from_center = fabs((double)curr_x - WIDTH / 2.0) / (WIDTH / 2.0);
    double vignette_factor = 1.0 - dist_from_center * vignette_strength;
    if (vignette_factor < 0.0) vignette_factor = 0.0;
    int r = ((color >> 16) & 0xFF) * vignette_factor;
    int g = ((color >> 8) & 0xFF) * vignette_factor;
    int b = (color & 0xFF) * vignette_factor;
    return ((r << 16) | (g << 8) | b);
}

