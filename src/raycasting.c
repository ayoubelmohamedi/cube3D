/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:07 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/23 09:05:05 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 3, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

void my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = env->addr + (y * env->line_lenght + x * (env->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}


void render_floor(t_player *player, int screen_x, int y_start, int y_end, int wall_height)
{
    (void) y_start;
    (void) wall_height;

    double playerDirX = cos(player->dir);
    double playerDirY = sin(player->dir);

    double fov_rad = FOV * (M_PI / 180); 

    double planeX = -playerDirY * tan(FOV / 2.0);
    double planeY = playerDirX * tan(fov_rad / 2.0);

    for (int y = y_end; y < HEIGHT; y++)
    {
        double rowDistance = (0.5 * HEIGHT) / (y - HEIGHT / 2.0);

        float floorStepX = rowDistance * (playerDirX + planeX - (playerDirX - planeX)) / WIDTH;
        float floorStepY = rowDistance * (playerDirY + planeY - (playerDirY - planeY)) / WIDTH;

        float currentFloorX = player->x + rowDistance * (playerDirX - planeX);
        float currentFloorY = player->y + rowDistance * (playerDirY - planeY);
        
        currentFloorX += floorStepX * screen_x;
        currentFloorY += floorStepY * screen_x;

        int texX = (int)(player->env->texture->floor_width * (currentFloorX - floor(currentFloorX))) & (player->env->texture->floor_width - 2);
        int texY = (int)(player->env->texture->floor_height * (currentFloorY - floor(currentFloorY))) & (player->env->texture->floor_height - 1);

        int floor_color = FLOOR_COLOR;
        if (texX >= 0 && texX < player->env->texture->floor_width && texY >= 0 && texY < player->env->texture->floor_height)
        {
            char *tex_pixel_ptr = player->env->texture->floor_addr + (texY * player->env->texture->floor_line_len + texX * (player->env->texture->floor_bpp / 8));
            floor_color = *(unsigned int*) tex_pixel_ptr;
            floor_color = darken_color(floor_color, rowDistance);
            my_mlx_pixel_put(player->env, screen_x, y, floor_color);
        }
    }
} 

void render_ceiling(t_player *player, int screen_x, int y_start, int y_end, int wall_height)
{
    (void) y_end;
    (void) wall_height;

    double playerDirX = cos(player->dir);
    double playerDirY = sin(player->dir);

    double fov_rad = FOV * (M_PI / 180);

    double planeX = -playerDirY * tan(fov_rad / 2.0);
    double planeY = playerDirX * tan(fov_rad / 2.0);
    for (int y = 0; y < y_start; y++)
    {
        // distance from camera to ceiling pixel
        float rowDistance = (0.5 * HEIGHT) / (HEIGHT / 2.0 - y);

        // Calculate the real world step vector for this row (same as floor)
        float floorStepX = rowDistance * (playerDirX + planeX - (playerDirX - planeX)) / WIDTH;
        float floorStepY = rowDistance * (playerDirY + planeY - (playerDirY - planeY)) / WIDTH;

        // Calculate the real world coordinates of the leftmost pixel in this row
        float currentCeilX = player->x + rowDistance * (playerDirX - planeX);
        float currentCeilY = player->y + rowDistance * (playerDirY - planeY);

        // adjust to current screen_x column
        currentCeilX += floorStepX * screen_x;
        currentCeilY += floorStepY * screen_x;

        // Get texture coordinates
        int texX = (int)(player->env->texture->ceil_width * (currentCeilX - floor(currentCeilX))) & (player->env->texture->ceil_width - 1);
        int texY = (int)(player->env->texture->ceil_height * (currentCeilY - floor(currentCeilY))) & (player->env->texture->ceil_height - 1);

        int ceil_color = CEILING_COLOR;
        if (texX >= 0 && texX < player->env->texture->ceil_width && texY >= 0 && texY < player->env->texture->ceil_height)
        {
            char *tex_pixel_ptr = player->env->texture->ceil_addr + (texY * player->env->texture->ceil_line_len + texX * (player->env->texture->ceil_bpp / 8));
            ceil_color = *(unsigned int *)tex_pixel_ptr;
            // to apply distance darkning based on distance ?
        }
        my_mlx_pixel_put(player->env, screen_x, y, ceil_fog_color(ceil_color , rowDistance));
    }
}

void render_wall_tex(t_player *player, int y_start, int y_end, int curr_x, int corrected_dist, int rayDirX, int rayDirY, int side, int wall_height)
{
    char *texture_addr = NULL;
    int texture_width = 0;
    int texture_height = 0;
    int texture_bpp = 0;
    int texture_line_len = 0;

    switch (side) {
       case SIDE_NORTH:
           texture_addr = player->env->walls->north_addr; texture_width = player->env->walls->north_width; texture_height = player->env->walls->north_height;
           texture_bpp = player->env->walls->north_bpp; texture_line_len = player->env->walls->north_line_len; break;
       case SIDE_SOUTH:
           texture_addr = player->env->walls->south_addr; texture_width = player->env->walls->south_width; texture_height = player->env->walls->south_heght;
           texture_bpp = player->env->walls->south_bpp; texture_line_len = player->env->walls->south_line_len; break;
       case SIDE_EAST:
           texture_addr = player->env->walls->east_addr; texture_width = player->env->walls->east_width; texture_height = player->env->walls->east_height;
           texture_bpp = player->env->walls->east_bpp; texture_line_len = player->env->walls->east_line_len; break;
       case SIDE_WEST:
           texture_addr = player->env->walls->west_addr; texture_width = player->env->walls->west_width; texture_height = player->env->walls->west_height;
           texture_bpp = player->env->walls->west_bpp; texture_line_len = player->env->walls->west_line_len; break;
    }

    double wallX;

    if (side == SIDE_EAST || side == SIDE_WEST) // Hit on X-oriented wall
        wallX = player->y + corrected_dist * rayDirY;
    else
        wallX = player->x + corrected_dist * rayDirX; 

    wallX -= floor(wallX);
    int texX = (int) (wallX * (double) texture_width);

    if ((side == SIDE_EAST || side == SIDE_WEST) && rayDirX > 0) // Facing West wall
        texX = texture_width - texX - 1;
    if ((side == SIDE_NORTH || side == SIDE_SOUTH) && rayDirY < 0) // Facing South wall
        texX = texture_width - texX - 1;

    double step = 1.0 * texture_height / wall_height;
    // texY = (int)texPos % texture_height; // Alternative using modulo
    double texPos = (y_start - HEIGHT / 2.0 + wall_height / 2.0) * step;
 
    // draw walls
    int color = WALL_COLOR;
    for (int y = y_start; y < y_end; y++)
    {
        // int texY = (int)texPos & (texture_height - 1); //  optimized but works for even numbers only,  
        int texY = (int)texPos % texture_height;
        if (texY < 0) texY += texture_height;
        texPos += step;

        // int color = 0;
        if (texture_addr && texX >= 0 && texX < texture_width && texY >= 0 && texY < texture_height) {
            char *dst = texture_addr + (texY * texture_line_len + texX * (texture_bpp / 8));
            color = *(unsigned int *)dst;
        }
        // Apply vignette (optional)
        color = darken_color(color, corrected_dist);
        color  = vignette_effect(curr_x, color);
        my_mlx_pixel_put(player->env, curr_x, y, color);
    }
}





int handle_keypress(int keypress, t_player *player)
{
    bool need_render = false;

    if (keypress == KEY_ESC)
    {
        mlx_destroy_image(player->env->mlx, player->env->img);
        mlx_destroy_window(player->env->mlx, player->env->win);
        exit(0);
    }
    if (keypress == KEY_W)
    {
        double new_x = player->x + cos(player->dir) * MOVE_SPEED;
        double new_y = player->y + sin(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
        need_render = true;
    }
    if (keypress == KEY_S)
    {
        double new_x = player->x - cos(player->dir) * MOVE_SPEED;
        double new_y = player->y - sin(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
        need_render = true;
    }
    if (keypress == KEY_A)
    {
        double new_x = player->x + sin(player->dir) * MOVE_SPEED;
        double new_y = player->y - cos(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
        need_render = true;
    }
    if (keypress == KEY_D)
    {
        double new_x = player->x - sin(player->dir) * MOVE_SPEED;
        double new_y = player->y + cos(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
        need_render = true;
    }
    if (keypress == KEY_LEFT)
    {
        player->dir -= ROTATE_SPEED;
        if (player->dir < 0)
            player->dir += 2 * M_PI;
        need_render = true;
    }
    if (keypress == KEY_RIGHT)
    {
        player->dir += ROTATE_SPEED;
        if (player->dir >= 2 * M_PI)
            player->dir -= 2 * M_PI;
        need_render = true; 
    }
    if (need_render)
        render_scene(player->env, player);
    return (0);
}

int main()
{
    t_env env;
    t_texture texture;
    t_wall_text wall_tex;

    char *sky[] = {"assets/sky/minecraft.xpm",
                   "assets/sky/minecraft.xpm",
                   "assets/sky/minecraft2.xpm",
                   "assets/sky/sunset.xpm",
                   "assets/sky/zenith.xpm",
                   NULL};

    // concrete & grass & planks
    char *floor[] = { "assets/floor/concrete/lime.xpm",
        "assets/floor/concrete/yellow.xpm",
        "assets/floor/grass/AC.xpm",
        "assets/floor/planks/birch.xpm",
        NULL
    };


    char *walls_no[] = {"assets/walls/stone_bricks/1.xpm", NULL};
    char *walls_so[] = {"assets/walls/stone_bricks/2.xpm", NULL};
    char *walls_ea[] = {"assets/walls/stone_bricks/3.xpm", NULL}; 
    char *walls_we[] = {"assets/walls/stone_bricks/4.xpm", NULL};

    // adaptive part
    texture.has_ceiling = true;
    texture.has_floor = true;
    env.has_texture = true;
    env.has_wall_texture = true;
    env.texture = &texture;
    env.walls = &wall_tex;

    env.mlx = mlx_init();
    env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "Raycasting Demo");

    env.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);

    env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel,
                                 &env.line_lenght, &env.endian);

    texture.ceil_img = mlx_xpm_file_to_image(env.mlx, sky[3], &env.texture->ceil_width, &env.texture->ceil_height);
    if (!env.texture->ceil_img)
    { 
        mlx_destroy_image(env.mlx, env.img);
        mlx_destroy_window(env.mlx, env.win);
        perror("celiling image error");
        return (1);
    }
    texture.floor_img = mlx_xpm_file_to_image(env.mlx, floor[1], &env.texture->floor_width, &env.texture->floor_height);
    if (!env.texture->ceil_img)
    {
        // exit
        // ft_destory();
        //  print_error();
        mlx_destroy_image(env.mlx ,texture.ceil_img);
        mlx_destroy_image(env.mlx, env.img);
        mlx_destroy_window(env.mlx, env.win);
        perror("floor image error");
        return (1);
    }


    // load wall textures
    wall_tex.north_img = mlx_xpm_file_to_image(env.mlx, walls_no[0], &env.walls->north_width, &env.walls->north_height);
    if (!wall_tex.north_img) { return (1); }
    wall_tex.north_addr = mlx_get_data_addr(env.walls->north_img, &env.walls->north_bpp, &env.walls->north_line_len, &env.walls->north_endian);

    wall_tex.south_img = mlx_xpm_file_to_image(env.mlx, walls_so[0], &env.walls->south_width, &env.walls->south_heght);
    if (!wall_tex.south_img) { return (1); }
    wall_tex.south_addr = mlx_get_data_addr(env.walls->south_img, &env.walls->south_bpp, &env.walls->south_line_len, &env.walls->south_endian);

    wall_tex.east_img = mlx_xpm_file_to_image(env.mlx, walls_ea[0], &env.walls->east_width, &env.walls->east_height);
    if (!wall_tex.east_img) { return (1); }
    wall_tex.east_addr = mlx_get_data_addr(env.walls->east_img, &env.walls->east_bpp, &env.walls->east_line_len, &env.walls->east_endian);

    wall_tex.west_img = mlx_xpm_file_to_image(env.mlx, walls_we[0], &env.walls->west_width, &env.walls->west_height);
    if (!wall_tex.west_img) { return (1); }
    wall_tex.west_addr = mlx_get_data_addr(env.walls->west_img, &env.walls->west_bpp, &env.walls->west_line_len, &env.walls->west_endian);  

    // load addrs of floor and ceiling
    env.texture->floor_addr = mlx_get_data_addr(env.texture->floor_img, &env.texture->floor_bpp, &env.texture->floor_line_len, &env.texture->floor_endian);
    env.texture->ceil_addr = mlx_get_data_addr(env.texture->ceil_img, &env.texture->ceil_bpp, &env.texture->ceil_line_len, &env.texture->ceil_endian);

    double player_x = 3.5;
    double player_y = 3.5;

    t_player player = {player_x, player_y, M_PI / 2, &env}; // center of map, facing down

    player.env = &env;
    env.has_minimap = true;
    render_scene(&env, &player);

    mlx_hook(env.win, 2, 1L << 0, handle_keypress, &player);

    mlx_loop(env.mlx);
    return 0;
}
