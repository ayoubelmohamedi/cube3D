/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:09 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/23 12:07:18 by ael-moha         ###   ########.fr       */
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

/*          colors & effects          */
static int  handle_exit(t_player *player);
static int  handle_movement(int key, t_player *player);
static int  handle_rotation(int key, t_player *player);
int         handle_keypress(int keypress, t_player *player);

/*             DDA algo                */
static void	init_dda(double rayDirX, double rayDirY, double *rayX,
            double *rayY, int *mapX, int *mapY, t_dda *dda);
static int	perform_dda(int *mapX, int *mapY, t_dda *dda);
double	dda_algo(double rayDirX, double rayDirY, double *rayX,
            double *rayY, int *mapX, int *mapY, int *side);


#endif 
