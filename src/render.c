/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:58:26 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 18:17:44 by ael-moha         ###   ########.fr       */
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
    env->addr= mlx_get_data_addr(env->img, &env->bits_per_pixel,
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


void fill_rays(t_rays * rays, t_player *player, double ray_angle)
{
    rays->rayX = &player->x;
    rays->rayY = &player->y;
    rays->rayDirX = cos(ray_angle);
    rays->rayDirY = sin(ray_angle);
    rays->mapX = (int) rays->rayX;
    rays->mapY = (int) rays->rayY;
}


void fill_vertical_info(t_vertical_info * info, int screen_x, int wall_height, double correct_dist)
{
    info->x = screen_x;
    info->wall_height = wall_height;
    info->corrected_dist = correct_dist;
}

void cast_ray(t_player *player, double ray_angle, int screen_x)
{
    t_rays rays;
    t_vertical_info info;
    int side;

    fill_rays(&rays, player, ray_angle);
    info.rayDirX = rays.rayDirX;
    info.rayDirY = rays.rayDirY;
    if (rays.mapX < 0 || rays.mapX >= player->env->map_width || rays.mapY < 0 || rays.mapY >= player->env->map_height)
        return;
    double dist = dda_algo(&rays, &side, player);
    if (dist >= 0)
    {
        // fix bowelfish effect
        double correct_dist = dist * cos(ray_angle - player->dir);
        if (correct_dist < 0.01)
            correct_dist = 0.01;

        int wall_height = (int)(HEIGHT / correct_dist);
        if (wall_height < 0)
            wall_height = 0;
        if (wall_height > HEIGHT)
            wall_height = HEIGHT;
        info.side = side;
        fill_vertical_info(&info, screen_x, wall_height, correct_dist);
        draw_vertical_line(player, info);
    }
}

void draw_vertical_line(t_player *player, t_vertical_info info)
{
    int y_start = (HEIGHT - info.wall_height) / 2;
    if (y_start < 0) y_start = 0;
    int y_end = y_start + info.wall_height;
    if (y_end  > HEIGHT ) y_end = HEIGHT;

    // draw ceiling
    if (player->env->has_texture && player->env->texture->has_ceiling)
        render_ceiling(player, info.x, y_start, y_end, info.wall_height);
    else
        for (int y = 0; y < y_start; y++)
            my_mlx_pixel_put(player->env, info.x, y, player->env->c_color);
    
    if (player->env->has_wall_texture)
        render_wall_tex(player, y_start, y_end, info);
    else
        for (int y = y_start; y < y_end; y++)
            my_mlx_pixel_put(player->env, info.x, y, vignette_effect(info.x, WALL_COLOR));

    // draw floor
    if (player->env->has_texture && player->env->texture->has_floor)
        render_floor(player, info.x, y_end);
    else
        for (int y = y_end; y < HEIGHT; y++)
            my_mlx_pixel_put(player->env, info.x, y, player->env->f_color);
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