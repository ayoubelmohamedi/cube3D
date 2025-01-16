

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800 
# define HEIGHT 600 
# define MAP_WIDTH 20
# define MAP_HEIGHT 10
#define TILE_SIZE 30

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
    int map[MAP_HEIGHT][MAP_WIDTH];
    Color color;
    void *mlx;
    void *win;
    int player_x;
    int player_y;
    int map_height;
    int map_width;
} Game;

#endif /* CUB3D_H */
