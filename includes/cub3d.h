

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>

# define WIDTH 800 
# define HEIGHT 600
# define PROJ_PLANE_W 320
# define PROJ_PLANE_H 200
# define MAX_WIDTH 20 - 1
# define MAX_HEIGHT 10
#define TILE_SIZE 32

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    int r, g, b;
} Color;

typedef struct {
    Vector3 center;
    float radius;
    Vector3 color;
} Sphere;

typedef struct {
    Vector3 position;
    Vector3 direction;
} Ray;


typedef struct 
{
    int map[MAX_WIDTH][MAX_WIDTH];
    int player_x;
    int player_y;
    int fov;
    int dir;
    void *mlx;
    void *win;
    void *img;
    void *addr;
    int line_length;
    int bits_per_pixel; 
    int endian;
} t_game;


#endif /* CUB3D_H */
