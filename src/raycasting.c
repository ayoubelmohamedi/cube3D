

#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 640
#define HEIGHT 480
#define MAP_WIDTH 8
#define MAP_HEIGHT 8
#define TILE_SIZE 64
#define FOV 60
#define MOVE_SPEED 0.1
#define M_PI 3.14159265358979323846

#define CEILING_COLOR 0x87CEEB // Light Sky Blue
#define FLOOR_COLOR 0x8B4513

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

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
    t_texture *texture;
} t_env;

typedef struct
{
    double x, y;
    double dir;
    t_env *env;
} t_player;

int map[8][8] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 2, 0, 3, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}};

void my_mlx_pixel_put(t_env *env, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = env->addr + (y * env->line_lenght + x * (env->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

// Choose wall color by type
int get_color(int wall_type)
{
    if (wall_type == 1)
        return 0xFF0000; // Red
    if (wall_type == 2)
        return 0x00FF00; // Green
    if (wall_type == 3)
        return 0x0000FF; // Blue
    return 0xAAAAAA;
}

// Darken the color based on distance
int darken_color(int color, double dist)
{
    double factor = 1.0 / (1.0 + dist * 0.05); // fade with distance
    int r = ((color >> 16) & 0xFF) * factor;
    int g = ((color >> 8) & 0xFF) * factor;
    int b = (color & 0xFF) * factor;
    return (r << 16) | (g << 8) | b;
}

void render_floor(t_player *player, int screen_x, int y_start, int y_end, int height)
{
    (void)player;
    (void)screen_x;
    (void)y_start;
    (void)y_end;
    (void)height;
    return;
} 

void render_ceiling(t_player *player, int screen_x, int y_start, int y_end, int height)
{

    (void) y_end;
    (void) height;

    double playerDirX = cos(player->dir);
    double playerDirY = sin(player->dir);

    double fov_rad = FOV * (M_PI / 180);

    double planeX = -playerDirY * tan(fov_rad / 2.0);
    double planeY = playerDirX * tan(fov_rad / 2.0);
    for (int y = -1; y < y_start; y++)
    {
        // distance from camera to ceiling pixel
        float rowDistance = (-1.5 * HEIGHT) / (HEIGHT / 2.0 - y);

        // Calculate the real world step vector for this row (same as floor)
        float floorStepX = rowDistance * (playerDirX + planeX - (playerDirX - planeX)) / WIDTH;
        float floorStepY = rowDistance * (playerDirY + planeY - (playerDirY - planeY)) / WIDTH;

        // Calculate the real world coordinates of the leftmost pixel in this row
        float currentCeilX = player->x + rowDistance * (playerDirX - planeX);
        float currentCeilY = player->y + rowDistance * (playerDirY - planeY);

        // adjust to current screen_x column
        currentCeilX += floorStepX * screen_x;
        currentCeilY += floorStepY * screen_x;

        // Get texture coordinates
        int texX = (int)(player->env->texture->ceil_width * (currentCeilX - floor(currentCeilX))) & (player->env->texture->ceil_width - 1);
        int texY = (int)(player->env->texture->ceil_height * (currentCeilY - floor(currentCeilY))) & (player->env->texture->ceil_height - 1);

        int ceil_color = 0;
        if (texX >= 0 && texX < player->env->texture->ceil_width && texY >= 0 && texY < player->env->texture->ceil_height)
        {
            char *tex_pixel_ptr = player->env->texture->ceil_addr + (texY * player->env->texture->ceil_line_len + texX * (player->env->texture->ceil_bpp / 8));
            ceil_color = *(unsigned int *)tex_pixel_ptr;
            // to apply distance darkning based on distance ?
        }
        my_mlx_pixel_put(player->env, screen_x, y, ceil_color);
    }
}

void draw_vertical_line(t_player *player, int x, int height, int color)
{
    int y_start = (HEIGHT - height) / 2;
    int y_end = y_start + height;

    // draw ceiling
    if (player->env->has_texture && player->env->texture->has_ceiling)
        render_ceiling(player, x, y_start, y_end, height);
    else
        for (int y = 0; y < y_start; y++)
            my_mlx_pixel_put(player->env, x, y, CEILING_COLOR);

    // draw walls
    for (int y = y_start; y < y_end; y++)
        my_mlx_pixel_put(player->env, x, y, color);

    // draw floor
    if (player->env->has_texture && player->env->texture->has_floor)
        render_floor(player, x, y_start, y_end, height);
    else
        for (int y = y_end; y < HEIGHT; y++)
            my_mlx_pixel_put(player->env, x, y, FLOOR_COLOR);
}

double dda_algo(double rayDirX, double rayDirY, double *rayX, double *rayY, int *mapX, int *mapY)
{

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
    while (1)
    {
        // Jump to the next grid cell
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            *mapX += stepX;
            side_hit = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            *mapY += stepY;
            side_hit = 1; // hit a horizontal wall
        }

        // check bound before check
        if (*mapX < 0 || *mapX >= MAP_WIDTH || *mapY < 0 || *mapY >= MAP_HEIGHT)
            return (-1.0);

        // Check if a wall is hit
        if (map[*mapY][*mapX] > 0)
        {
            break;
        }
    }
    // (wallX - playerX + (1 - stepX) / 2) / rayDirX
    if (side_hit == 0)
        return (sideDistX - deltaDistX); // simplified
    else
        return (sideDistY - deltaDistY);
}

void cast_ray(t_player *player, double ray_angle, int screen_x)
{
    double rayX = player->x;
    double rayY = player->y;

    double rayDirX = cos(ray_angle);
    double rayDirY = sin(ray_angle);

    int mapX = (int)rayX;
    int mapY = (int)rayY;
    if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT)
        return;

    double dist = dda_algo(rayDirX, rayDirY, &rayX, &rayY, &mapX, &mapY);
    if (dist >= 0)
    {
        // fix bowelfish effect
        double correct_dist = dist * cos(ray_angle - player->dir);
        if (correct_dist < 0.01)
            correct_dist = 0.01;

        int wall_type = map[mapY][mapX];
        int wall_height = (int)(HEIGHT / correct_dist);
        if (wall_height < 0)
            wall_height = 0;
        if (wall_height > HEIGHT)
            wall_height = HEIGHT;
        int color = get_color(wall_type);
        color = darken_color(color, correct_dist);

        // 2. Apply screen-edge darkening (vignette)
        double vignette_strength = 0.4; // Adjust 0.0 (none) to 1.0 (black edges)
        // Calculate distance from center screen (0.0 center, 1.0 edges)
        double dist_from_center = fabs((double)screen_x - WIDTH / 2.0) / (WIDTH / 2.0);
        // Calculate darkening factor (closer to 0 means darker)
        double vignette_factor = 1.0 - dist_from_center * vignette_strength;
        if (vignette_factor < 0.0)
            vignette_factor = 0.0; // Clamp

        // Apply vignette factor to the color components
        int r = ((color >> 16) & 0xFF) * vignette_factor;
        int g = ((color >> 8) & 0xFF) * vignette_factor;
        int b = (color & 0xFF) * vignette_factor;
        color = (r << 16) | (g << 8) | b;

        draw_vertical_line(player, screen_x, wall_height, color);
    }
}

// Main render function
void render_scene(t_env *env, t_player *player)
{
    double fov_rad = (FOV * M_PI) / 180.0;

    mlx_destroy_image(env->mlx, env->img);
    env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
    mlx_get_data_addr(env->img, &env->bits_per_pixel,
                      &env->line_lenght, &env->endian);

    for (int x = 0; x < WIDTH; x++)
    {
        double ray_angle = player->dir - (fov_rad / 2.0) + (x * fov_rad / WIDTH);
        cast_ray(player, ray_angle, x);
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
    render_scene(player->env, player);

    return (0);
}

int main()
{
    t_env env;
    t_texture texture;

    char *sky[] = {"assets/sky/minecraft.xpm",
                   "assets/sky/minecraft.xpm",
                   "assets/sky/minecraft2.xpm",
                   "assets/sky/sunset.xpm",
                   "assets/sky/zenith.xpm",
                   NULL};

    // adaptive part
    texture.has_ceiling = true;
    texture.has_floor = false;
    env.has_texture = true;
    env.texture = &texture;

    env.mlx = mlx_init();
    env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "Raycasting Demo");

    env.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);

    env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel,
                                 &env.line_lenght, &env.endian);

    texture.ceil_img = mlx_xpm_file_to_image(env.mlx, sky[0], &env.texture->ceil_width, &env.texture->ceil_height);
    if (!env.texture->ceil_img)
    {
        // exit
        // ft_destory();
        //  print_error();
        mlx_destroy_image(env.mlx, env.img);
        mlx_destroy_window(env.mlx, env.win);
        perror("celiling image error");
        return (1);
    }
    env.texture->ceil_addr = mlx_get_data_addr(env.texture->ceil_img, &env.texture->ceil_bpp, &env.texture->ceil_line_len, &env.texture->ceil_endian);

    double player_x = 3.5;
    double player_y = 3.5;

    t_player player = {player_x, player_y, M_PI / 2, &env}; // center of map, facing down

    player.env = &env;

    render_scene(&env, &player);

    mlx_hook(env.win, 2, 1L << 0, handle_keypress, &player);

    mlx_loop(env.mlx);
    return 0;
}
