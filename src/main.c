/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:42 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/24 16:32:46 by ael-moha         ###   ########.fr       */
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


t_texture *  load_floor_ceiling_texture(t_env * env)
{
    t_texture *w_texture;

    w_texture = (t_texture *)malloc(sizeof(t_texture));
    if (!w_texture)
        return (NULL);
    w_texture->ceil_img = mlx_xpm_file_to_image(env->mlx, env->textures_files[0], &w_texture->ceil_width, &w_texture->ceil_height);
    if (!w_texture->ceil_img)
    { 
        mlx_destroy_image(env->mlx, env->img);
        mlx_destroy_window(env->mlx, env->win);
        perror("celiling image error");
        return (1);
    }
    w_texture->floor_img = mlx_xpm_file_to_image(env->mlx, env->textures_files[1], &w_texture->floor_width, &w_texture->floor_height);
    if (!w_texture->ceil_img)
    {
        mlx_destroy_image(env->mlx, w_texture->ceil_img);
        mlx_destroy_image(env->mlx, env->img);
        mlx_destroy_window(env->mlx, env->win);
        perror("floor image error");
        return (1);
    }
    w_texture->floor_addr = mlx_get_data_addr(w_texture->floor_img, &w_texture->floor_bpp, &w_texture->floor_line_len, &w_texture->floor_endian);
    w_texture->ceil_addr = mlx_get_data_addr(w_texture->ceil_img, &w_texture->ceil_bpp, &w_texture->ceil_line_len, &w_texture->ceil_endian);
    return (w_texture);
}

t_wall_text *load_walls_texture(t_env *env)
{
    t_wall_text *walls_tex;
    
    walls_tex = (t_wall_text *) malloc(sizeof(t_wall_text));
    if (!walls_tex)
        return (NULL);
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

    
    return (walls_tex);
} 

int    load_env(t_env *env)
{
    env = (t_env *)malloc(sizeof(t_env));   
    if (!env)
        return (0);
    env->mlx = mlx_init();
    env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Raycasting Demo");
    env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
                                 &env->line_lenght, &env->endian);
    env->has_minimap = false;
    env->has_texture = true;
    env->has_wall_texture = true;
    env->texture = load_floor_ceiling_texture(env);
    env->walls = load_walls_texture(env); 
}


int main()
{
    t_env env;
    t_texture texture;
    t_wall_text wall_tex;


    // init_env + init_mlx 
    // to handle spawning orientaiton and postion based on player (x,y) and {S,E,W,N} 
    // make player rotation with mouse intead 
    // load ceiling and floor (if exist), else (no texture file) load default colors.
    // load walls texture, else load default colors? 
    




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
