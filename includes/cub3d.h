/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:09 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/25 18:07:28 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
#define CUB3D_H

#include "game_macros.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//to be deleted later 
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
char *floors[] = { "assets/floor/concrete/lime.xpm",
    "assets/floor/concrete/yellow.xpm",
    "assets/floor/grass/AC.xpm",
    "assets/floor/planks/birch.xpm",
    NULL
};

char *walls_no[] = {"assets/walls/stone_bricks/1.xpm", NULL};
char *walls_so[] = {"assets/walls/stone_bricks/2.xpm", NULL};
char *walls_ea[] = {"assets/walls/stone_bricks/3.xpm", NULL}; 
char *walls_we[] = {"assets/walls/stone_bricks/4.xpm", NULL};



typedef struct
{
    void *north_img;
    char *north_addr;
    int north_bpp;
    int north_line_len;
    int north_endian;
    int north_width;
    int north_height;

    void *south_img;
    char *south_addr;
    int south_bpp;
    int south_line_len;
    int south_endian;
    int south_width;
    int south_heght;

    void *east_img;
    char *east_addr;
    int east_bpp;
    int east_line_len;
    int east_endian;
    int east_width;
    int east_height;

    void *west_img;
    char *west_addr;
    int west_bpp;
    int west_line_len;
    int west_endian;
    int west_width;
    int west_height;
}   t_wall_text;

typedef struct
{
    bool has_floor;
    void *floor_img;
    char *floor_addr;
    int floor_bpp;
    int floor_line_len;
    int floor_endian;
    int floor_width;
    int floor_height;

    bool has_ceiling;
    void *ceil_img;
    char *ceil_addr;
    int ceil_bpp;
    int ceil_line_len;
    int ceil_endian;
    int ceil_width;
    int ceil_height;

} t_texture;

typedef struct
{
    char *textures_files[2];
    char *wall_tex_files[4];
    void *mlx;
    void *win;
    void *addr;
    void *img;
    int endian;
    int line_lenght;
    int bits_per_pixel;
    bool has_texture;
    bool has_wall_texture;
    bool has_minimap; 
    t_texture *texture;
    t_wall_text *walls;
} t_env;

typedef struct
{
    double x, y;
    double dir;
    t_env *env;
} t_player;

/*          Hooks          */
int         handle_keypress(int keypress, t_player *player);

/*             DDA algo                */
double	dda_algo(double rayDirX, double rayDirY, double *rayX,
            double *rayY, int *mapX, int *mapY, int *side);

/*              render minimap          */
void render_minimap(t_env *env, t_player *player);
void render_scene(t_env *env, t_player *player);

/*             colors & effects         */
int get_color(int wall_type);
int darken_color(int color, double dist);
int ceil_fog_color(int ceil_color, int rowDistance);
int vignette_effect(int curr_x, int color);


/*             mlx functions          */
void my_mlx_pixel_put(t_env *env, int x, int y, int color);

/*              Raycasting Core          */
void cast_ray(t_player *player, double ray_angle, int screen_x);
void draw_vertical_line(t_player *player, int rayDirX, int rayDirY, int x,
                     int wall_height, double corrected_dist, int side);
                    

/*              Rendering Components          */
void render_ceiling(t_player *player, int screen_x, int y_start, 
                   int y_end, int wall_height);
void render_floor(t_player *player, int screen_x, int y_start, 
                  int y_end, int wall_height);
void render_wall_tex(t_player *player, int y_start, int y_end, int curr_x,
                    double corrected_dist, double rayDirX, double rayDirY, 
                    int side, int wall_height);
#endif 
