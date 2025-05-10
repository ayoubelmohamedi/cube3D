/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:09 by ael-moha          #+#    #+#             */
/*   Updated: 2025/05/10 19:53:12 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
#define CUB3D_H

#include "game_macros.h"
#include  "../src/parsing/parsing.h"
#include "norm_helpers.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern char *sky[];
extern char *floors[];


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
    char **map;
    int c_color;
    int f_color;
    int map_width;
    int map_height;
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
double	dda_algo(t_rays *rays, int *side, t_player *player);

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
void draw_vertical_line(t_player *player, t_vertical_info info);
                    

/*              Rendering Components          */
void render_ceiling(t_player *player, int screen_x, int y_start);
void render_floor(t_player *player, int curr_x, int y_end);
void	render_wall_tex(t_player *player, int y_start, int y_end, t_vertical_info info);
#endif 
