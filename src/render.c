/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:58:26 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 23:06:06 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/cub3d.h"


// Main render function
void render_scene(t_env *env, t_player *player)
{
    double fov_rad = (FOV * M_PI) / 180.0;

    if (env->img)
        mlx_destroy_image(env->mlx, env->img);
    env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    mlx_get_data_addr(env->img, &env->bits_per_pixel,
                      &env->line_lenght, &env->endian);

    for (int x = 0; x < WIDTH; x++)
    {
        double ray_angle = player->dir - (fov_rad / 2.0) + (x * fov_rad / WIDTH);
        cast_ray(player, ray_angle, x);
    }
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
    if (env->has_minimap)
        render_minimap(env, player);
}

void cast_ray(t_player *player, double ray_angle, int screen_x)
{
    double rayX = player->x;
    double rayY = player->y;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);

    int mapX = (int)rayX;
    int mapY = (int)rayY;
    int side;

    if (mapX < 0 || mapX >= player->env->map_width || mapY < 0 || mapY >= player->env->map_height)
        return;

    double dist = dda_algo(rayDirX, rayDirY, &rayX, &rayY, &mapX, &mapY, &side, player);
    if (dist >= 0)
    {
        // fix bowelfish effect
        double correct_dist = dist * cos(ray_angle - player->dir);
        if (correct_dist < 0.01)
            correct_dist = 0.01;

        // int wall_type = map[mapY][mapX];
        int wall_height = (int)(HEIGHT / correct_dist);
        if (wall_height < 0)
            wall_height = 0;
        if (wall_height > HEIGHT)
            wall_height = HEIGHT;
        // int color = get_color(wall_type);
        // color = darken_color(color, correct_dist);

        draw_vertical_line(player, rayDirX, rayDirY,screen_x, wall_height,correct_dist, side);
    }
}

void draw_vertical_line(t_player *player, int rayDirX, int rayDirY, int x, int wall_height, double corrected_dist, int side)
{
    int y_start = (HEIGHT - wall_height) / 2;
    if (y_start < 0) y_start = 0;
    int y_end = y_start + wall_height;
    if (y_end  > HEIGHT ) y_end = HEIGHT;

    // draw ceiling
    if (player->env->has_texture && player->env->texture->has_ceiling)
        render_ceiling(player, x, y_start, y_end, wall_height);
    else
        for (int y = 0; y < y_start; y++)
            my_mlx_pixel_put(player->env, x, y, player->env->c_color);
    
    if (player->env->has_wall_texture)
        render_wall_tex(player, y_start, y_end,x,  corrected_dist, rayDirX, rayDirY, side, wall_height);
    else
        for (int y = y_start; y < y_end; y++)
            my_mlx_pixel_put(player->env, x, y, vignette_effect(x, WALL_COLOR));

    // draw floor
    if (player->env->has_texture && player->env->texture->has_floor)
        render_floor(player, x, y_start, y_end, wall_height);
    else
        for (int y = y_end; y < HEIGHT; y++)
            my_mlx_pixel_put(player->env, x, y, player->env->f_color);
}

void my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = env->addr + (y * env->line_lenght + x * (env->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}