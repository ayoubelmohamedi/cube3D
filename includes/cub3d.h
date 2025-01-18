

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// # define WIN_WIDTH 800 
// # define WIN_HEIGHT 600 
// # define MAP_WIDTH 20
// # define MAP_HEIGHT 10
// #define TILE_SIZE 30


// // #define TILE_SIZE 40
//     #define ROWS 10
//     #define COLS 19

//     // Define colors
//     #define COLOR_WALL 0xFFFFFF  // White
//     #define COLOR_PATH 0x000000  // Black
//     #define COLOR_PLAYER 0xFF0000 // Red

//     #define KEY_W 13 // Move up
//     #define KEY_A 0  // Move left
//     #define KEY_S 1  // Move down
//     #define KEY_D 2  // Move right
//     #define KEY_ESC 53 // Exit

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

// typedef struct 
// {
//     char map[ROWS][COLS + 1];
//     Color color;
//     void *mlx;
//     void *win;
//     int player_x;
//     int player_y;
//     int map_height;
//     int map_width;
// } Game;

#endif /* CUB3D_H */
