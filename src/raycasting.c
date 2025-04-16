

#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
    void *addr;
    void *img;
    int endian;
    int line_lenght;
    int bits_per_pixel; 
    
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

void	my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
	char	*dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
	dst = env->addr + (y * env->line_lenght + x * (env->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
    }
}


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
    {
        my_mlx_pixel_put(env,x, y, color);
        // mlx_pixel_put(env->mlx, env->win, x, y, color);
    } 
}

double dda_algo(double rayDirX, double rayDirY, double *rayX, double *rayY, int *mapX, int *mapY) {

    int side_hit = 0;
    // Initialize mapX and mapY to the player's current grid position
    *mapX = (int)(*rayX);
    *mapY = (int)(*rayY);

    // Calculate delta distances
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // Determine step direction and initial side distances
    int stepX = (rayDirX < 0) ? -1 : 1;
    int stepY = (rayDirY < 0) ? -1 : 1; 

    double sideDistX = (rayDirX < 0) ? (*rayX - *mapX) * deltaDistX : (*mapX + 1.0 - *rayX) * deltaDistX;
    double sideDistY = (rayDirY < 0) ? (*rayY - *mapY) * deltaDistY : (*mapY + 1.0 - *rayY) * deltaDistY;
    
    // Perform DDA
    while (1) {
        // Jump to the next grid cell
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            *mapX += stepX;
            side_hit = 0;
        } else {
            sideDistY += deltaDistY;
            *mapY += stepY;
            side_hit = 1; // hit a horizontal wall
        }

        // check bound before check 
        if (*mapX < 0 || *mapX >= MAP_WIDTH || *mapY < 0 || *mapY >= MAP_HEIGHT)
            return (-1.0);
        

        // Check if a wall is hit
        if (map[*mapY][*mapX] > 0) {
            break;
        }
    }
    // (wallX - playerX + (1 - stepX) / 2) / rayDirX
    if (side_hit == 0)
        return (sideDistX - deltaDistX); // simplified
    else
        return (sideDistY - deltaDistY);
}

void cast_ray(t_env *env, t_player player, double ray_angle, int screen_x) {
    double rayX = player.x;
    double rayY = player.y;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);
   
    int mapX = (int)rayX;
    int mapY = (int)rayY; 
    if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
        return ;  
        
    double dist = dda_algo(rayDirX, rayDirY, &rayX, &rayY, &mapX, &mapY);
    if (dist >= 0)
    {
        // fix bowelfish effect
        double correct_dist = dist * cos(ray_angle - player.dir);

        if (correct_dist < 0.01) correct_dist = 0.01;

        // printf("corrected dist => %f\n", correct_dist);
        int wall_type = map[mapY][mapX];
        int wall_height = (int)(HEIGHT / correct_dist);
        if (wall_height < 0) wall_height = 0;
        if (wall_height > HEIGHT) wall_height = HEIGHT;
        int color = get_color(wall_type);
        color = darken_color(color, dist);
        draw_vertical_line(env, screen_x, wall_height, color);
    }
    // for else, i could draw ceiling and wall ?
   
}

// Main render function
void render_scene(t_env *env, t_player player) {
    double fov_rad = (FOV * M_PI) / 180.0;

    mlx_destroy_image(env->mlx, env->img);
    env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    mlx_get_data_addr(env->img, &env->bits_per_pixel,
        &env->line_lenght, &env->endian);

    for (int x = 0; x < WIDTH; x++) {
        double ray_angle = player.dir - (fov_rad / 2.0) + (x * fov_rad / WIDTH);
        cast_ray(env, player, ray_angle, x);
    }
    mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}


int handle_keypress(int keypress, t_player *player)
{
    if (keypress == KEY_ESC)
    {
        mlx_destroy_image(player->env->mlx, player->env->img);
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
    
    env.img = mlx_new_image(env.mlx ,WIDTH, HEIGHT);

    env.addr =  mlx_get_data_addr(env.img, &env.bits_per_pixel,
        &env.line_lenght, &env.endian);
     
    double player_x = 3.5;
    double player_y = 3.5;

    t_player player = {player_x, player_y, M_PI / 2, &env}; // center of map, facing down

    render_scene(&env, player);

    mlx_hook(env.win,2, 1L << 0, handle_keypress, &player);

    mlx_loop(env.mlx);
    return 0;
}
