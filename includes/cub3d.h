/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:56:09 by ael-moha          #+#    #+#             */
/*   Updated: 2025/04/23 12:15:13 by ael-moha         ###   ########.fr       */
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

/*            ceiling render            */
static void	init_ceiling_render(t_player *player, t_ceil_render *cr);
static void	calc_ceiling_position(t_player *player, t_ceil_render *cr, int y);
static int	get_ceiling_color(t_player *player, t_ceil_render *cr);
void	render_ceiling(t_player *player, int screen_x, int y_start, 
                    int y_end, int wall_height);


/*            floor render            */
static void	init_floor_render(t_player *player, t_floor_render *fr);
static void	calc_floor_position(t_player *player, t_floor_render *fr, int y);
static void	get_floor_texture_coords(t_player *player, t_floor_render *fr);
static int	get_floor_color(t_player *player, t_floor_render *fr);
void	render_floor(t_player *player, int screen_x, int y_start, 
                                        int y_end, int wall_height);

/*            wall texture render            */
void	render_wall_tex(t_player *player, int y_start, int y_end, int curr_x,
    int corrected_dist, int rayDirX, int rayDirY, int side, 
    int wall_height);
static void	draw_wall_slice(t_player *player, t_wall_render *wr);
static int	get_texture_x(t_player *player, int side, double corrected_dist,
    int rayDirX, int rayDirY, int texture_width);
static void	get_texture_info(t_player *player, int side, char **texture_addr, 
    int *texture_width, int *texture_height, 
    int *texture_bpp, int *texture_line_len);

/*            wall texture render            */

void render_scene(t_env *env, t_player *player);
void cast_ray(t_player *player, double ray_angle, int screen_x);    
void draw_vertical_line(t_player *player, int rayDirX, int rayDirY, int x, int wall_height, double corrected_dist, int side); 
void my_mlx_pixel_put(t_env *env, int x, int y, int color);


#endif 
