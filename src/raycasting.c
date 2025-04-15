

#include "mlx.h"
#include <math.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64
#define FOV 60
#define MOVE_SPEED 0.1
#define M_PI 3.14159265358979323846

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

typedef struct {
    void *mlx;
    void *win;
} t_env;

typedef struct {
    double x, y;
    double dir;
    t_env *env;
} t_player;

int map[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,2,0,3,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

// Choose wall color by type
int get_color(int wall_type) {
    if (wall_type == 1)
        return 0xFF0000; // Red
    if (wall_type == 2)
        return 0x00FF00; // Green
    if (wall_type == 3)
        return 0x0000FF; // Blue
    return 0xAAAAAA;
}

// Darken the color based on distance
int darken_color(int color, double dist) {
    double factor = 1.0 / (1.0 + dist * 0.05); // fade with distance
    int r = ((color >> 16) & 0xFF) * factor;
    int g = ((color >> 8) & 0xFF) * factor;
    int b = (color & 0xFF) * factor;
    return (r << 16) | (g << 8) | b;
}

void draw_vertical_line(t_env *env, int x, int height, int color) {
    int y_start = (HEIGHT - height) / 2;
    int y_end = y_start + height;
    for (int y = y_start; y < y_end; y++)
        mlx_pixel_put(env->mlx, env->win, x, y, color);
}

// Cast a single ray and draw the result
void cast_ray(t_env *env, t_player player, double ray_angle, int screen_x) {
    double rayX = player.x;
    double rayY = player.y;
    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);
    
    while (1) {
        rayX += rayDirX * 0.05;
        rayY += rayDirY * 0.05;
        int mapX = (int)rayX;
        int mapY = (int)rayY;

        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
            break;
        if (map[mapY][mapX] > 0) {
            double dist = sqrt((rayX - player.x)*(rayX - player.x) + (rayY - player.y)*(rayY - player.y));
            int wall_type = map[mapY][mapX];
            int wall_height = (int)(HEIGHT / dist);

            int color = get_color(wall_type);
            color = darken_color(color, dist);

            draw_vertical_line(env, screen_x, wall_height, color);
            break;
        }
    }
}

// Main render function
void render_scene(t_env *env, t_player player) {
    double fov_rad = (FOV * M_PI) / 180.0;
    for (int x = 0; x < WIDTH; x++) {
        double ray_angle = player.dir - (fov_rad / 2.0) + (x * fov_rad / WIDTH);
        cast_ray(env, player, ray_angle, x);
    }
}


int handle_keypress(int keypress, t_player *player)
{
    if (keypress == KEY_ESC)
    {
        mlx_destroy_window(player->env->mlx, player->env->win);
        exit(0);
    }
    if (keypress == KEY_W)
    {
        double new_x = player->x + cos(player->dir) * MOVE_SPEED;
        double new_y = player->y + sin(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (keypress == KEY_S)
    {
        double new_x = player->x - cos(player->dir) * MOVE_SPEED;
        double new_y = player->y - sin(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
    } 
    if (keypress == KEY_A)
    {
        double new_x = player->x + sin(player->dir) * MOVE_SPEED;
        double new_y = player->y - cos(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (keypress == KEY_D)
    {
        double new_x = player->x - sin(player->dir) * MOVE_SPEED;
        double new_y = player->y + cos(player->dir) * MOVE_SPEED;
        if (map[(int)new_y][(int)new_x] == 0)
        {
            player->x = new_x;
            player->y = new_y;
        }
    }
    mlx_clear_window(player->env->mlx, player->env->win);
    render_scene(player->env, *player);

    return (0);
} 

int main() {
    t_env env;
    env.mlx = mlx_init();
    env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "Raycasting Demo");
    
    double player_x = 3.5;
    double player_y = 3.5;

    t_player player = {player_x, player_y, M_PI / 2, &env}; // center of map, facing down

    render_scene(&env, player);

    mlx_hook(env.win,2, 1L << 0, handle_keypress, &player);

    mlx_loop(env.mlx);
    return 0;
}
