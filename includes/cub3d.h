

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdbool.h>

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

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TILE_SIZE 40
#define ROWS 10
#define COLS 19

// Define colors
#define COLOR_WALL 0xFFFFFF  // White
#define COLOR_PATH 0x000000  // Black
#define COLOR_START 0xFF0000 // Red
#define COLOR_PLAYER 0x00FF00 // Green

// Define key codes (may vary by system)
#define KEY_W 119 // Move up
#define KEY_A 97  // Move left
#define KEY_S 115  // Move down
#define KEY_D 100  // Move right
#define KEY_ESC 65307 // Exit

typedef struct s_game {
    void *mlx;
    void *win;
    int changed;
    char map[ROWS][COLS + 1];
    int NUM_RAY;
    int player_angle;
    int player_x;
    int player_y;
} t_game;


#define PI 3.14159265358979323846 

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


void raycast(t_game *game);
void draw_wall(int x, int wall_height, int color, t_game *game);
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
