/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:15:42 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/05 21:21:49 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


/* Definitions of global variables here */

char *walls_no[] = {"assets/walls/stone_bricks/1.xpm", NULL};
char *walls_so[] = {"assets/walls/stone_bricks/2.xpm", NULL};
char *walls_ea[] = {"assets/walls/stone_bricks/3.xpm", NULL}; 
char *walls_we[] = {"assets/walls/stone_bricks/4.xpm", NULL};

char *sky[] = {"assets/sky/minecraft.xpm",
               "assets/sky/minecraft2.xpm", 
               "assets/sky/sunset.xpm",
               "assets/sky/zenith.xpm",
               NULL};

char *floors[] = {"assets/floor/concrete/lime.xpm",
                "assets/floor/concrete/yellow.xpm",
                NULL};

t_texture *  load_floor_ceiling_texture(t_env * env)
{
    t_texture *w_texture;

    w_texture = (t_texture *)malloc(sizeof(t_texture));
    if (!w_texture)
        return (NULL);
    w_texture->ceil_img = mlx_xpm_file_to_image(env->mlx, env->textures_files[0], &w_texture->ceil_width, &w_texture->ceil_height);
    // Todo, handle if no texture file exist [add default color]
    w_texture->has_ceiling = true;
    w_texture->has_floor = true;
    if (!w_texture->ceil_img)
    {
        w_texture->has_ceiling = false;
        w_texture->ceil_img = NULL;
        w_texture->ceil_addr = NULL;
        perror("celiling image error");
        return (NULL);
    }
    w_texture->floor_img = mlx_xpm_file_to_image(env->mlx, env->textures_files[1], &w_texture->floor_width, &w_texture->floor_height);
    if (!w_texture->floor_img)
    {
        w_texture->has_floor = false;
        w_texture->floor_img = NULL;
        w_texture->floor_addr = NULL;
        perror("floor image error");
        return (NULL);
    }
    if (w_texture->ceil_img)
        w_texture->ceil_addr = mlx_get_data_addr(w_texture->ceil_img, &w_texture->ceil_bpp, &w_texture->ceil_line_len, &w_texture->ceil_endian);
    if (w_texture->floor_img)
        w_texture->floor_addr = mlx_get_data_addr(w_texture->floor_img, &w_texture->floor_bpp, &w_texture->floor_line_len, &w_texture->floor_endian);
    return (w_texture);
}

t_wall_text *load_walls_texture(t_env *env)
{
    t_wall_text *walls_tex;
    
    walls_tex = (t_wall_text *) malloc(sizeof(t_wall_text));
    if (!walls_tex)
        return (NULL);
    walls_tex->north_img = mlx_xpm_file_to_image(env->mlx, env->wall_tex_files[0], &walls_tex->north_width, &walls_tex->north_height);
    if (!walls_tex->north_img) { return (NULL); }
    walls_tex->north_addr = mlx_get_data_addr(walls_tex->north_img, &walls_tex->north_bpp, &walls_tex->north_line_len, &walls_tex->north_endian);

    walls_tex->south_img = mlx_xpm_file_to_image(env->mlx, env->wall_tex_files[1], &walls_tex->south_width, &walls_tex->south_heght);
    if (!walls_tex->south_img) { return (NULL); }
    walls_tex->south_addr = mlx_get_data_addr(walls_tex->south_img, &walls_tex->south_bpp, &walls_tex->south_line_len, &walls_tex->south_endian);

    walls_tex->west_img = mlx_xpm_file_to_image(env->mlx,  env->wall_tex_files[2], &walls_tex->west_width, &walls_tex->west_height);
    if (!walls_tex->west_img) { return (NULL); }
    walls_tex->west_addr = mlx_get_data_addr(walls_tex->west_img, &walls_tex->west_bpp, &walls_tex->west_line_len, &walls_tex->west_endian);

        
    walls_tex->east_img = mlx_xpm_file_to_image(env->mlx,  env->wall_tex_files[3], &walls_tex->east_width, &walls_tex->east_height);
    if (!walls_tex->east_img) { return (NULL); }
    walls_tex->east_addr = mlx_get_data_addr(walls_tex->east_img, &walls_tex->east_bpp, &walls_tex->east_line_len, &walls_tex->east_endian);
    
    return (walls_tex);
} 

void init_texture_paths(t_env *env)
{
    // textures paths for [no, so, we,ea]
    env->wall_tex_files[0] = walls_no[0];
    env->wall_tex_files[1] = walls_so[0];
    env->wall_tex_files[2] = walls_we[0];
    env->wall_tex_files[3] = walls_ea[0];

    // textures for ceiling + floor 
    env->textures_files[0] = sky[0];
    env->textures_files[1] = floors[0];
}

t_player *init_player(t_env *env)
{
    t_player *player;

    player = (t_player*) malloc(sizeof(t_player));
    if (!player)
        return (NULL);
    player->env = env;
    player->x = 3.5;
    player->y = 3.5;
    player->dir =  M_PI / 2; //  facing down 
    return (player);
}

t_env    *load_env()
{
    t_env * env;

    env = (t_env *)malloc(sizeof(t_env));   
    if (!env)
        return (NULL);
    env->mlx = mlx_init();
    env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, "Raycasting Demo");
    env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel,
                                 &env->line_lenght, &env->endian);
    env->has_minimap = false;
    env->has_texture = true;
    init_texture_paths(env);
    env->has_wall_texture = true;
    env->texture = load_floor_ceiling_texture(env);
    env->walls = load_walls_texture(env);
    return (env);
}

int main()
{
    t_env *env;
    t_player *player;


    //[x] init_env + init_mlx 
    //[x] added funcs for loading textures to t_env. ([ceiling & floor] + walls ) 
    //[X] to handle spawning orientaiton and postion based on player (x,y) and {S,E,W,N} 
    // make player rotation with mouse intead 
    // load ceiling and floor (if exist), else (no texture file) load default colors.
    // load walls texture, else load default colors? 

    env = load_env();
    player = init_player(env);
    
    render_scene(env, player);

    mlx_hook(env->win, 2, 1L << 0, handle_keypress, player);
    mlx_loop(env->mlx);
    return 0;
}
