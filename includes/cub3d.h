

#ifndef CUB3D_H
#define CUB3D_H

#include "game_macros.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


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


#endif 
