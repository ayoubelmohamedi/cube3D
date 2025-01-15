#include "cub3d.h"
void my_put_pixel(void *mlx, void *win, int x, int y, Color color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        int rgb = (color.r << 16) | (color.g << 8) | color.b;
        mlx_pixel_put(mlx, win, x, y, rgb);
    }
}
// (x−cx)^2+(y−cy)^2+(z−cz)^2=r^2
void draw_sphere(void *mlx, void *win, Vector3 center, int radius, Color color) {
    for (int y = center.y - radius; y <= center.y + radius; y++) {
        for (int x = center.x - radius; x <= center.x + radius; x++) {
            int dx = x - center.x;
            int dy = y - center.y;
            if (dx * dx + dy * dy <= radius * radius) {
                my_put_pixel(mlx, win, x, y, color);
                // usleep(100);
            }
        }
    }
}
void parse_map(const char *filename, Game *game) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAP_WIDTH + 2]; // +2 for newline and null terminator
    int row = 0;
    int col = 0;
    while (fgets(line, sizeof(line), file)) {
        col = 0;
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++)
        {
            if (line[i] == 'S')
            {
                game->player_x = col;
                game->player_y = row;
            }
            else if (line[i] == '1' || line[i] == '0')
                game->map[row][col++] = line[i] - 48;
        }
        col = 0;
        row++;
    }
    game->map_width = MAP_WIDTH;
    game->map_height = MAP_HEIGHT;
    fclose(file);
}
void draw_square(void *mlx, void *win, int x, int y, int color) {
    printf("drawing a square in (%d, %d), color = %d\n", x, y, color);
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            mlx_pixel_put(mlx, win, x + i, y + j, color);
        }
    }
}

void draw_player(Game *game) {
    int px = game->player_x * TILE_SIZE + TILE_SIZE / 4; 
    int py = game->player_y * TILE_SIZE + TILE_SIZE / 4; 
    for (int i = 0; i < TILE_SIZE / 2; i++) {
        for (int j = 0; j < TILE_SIZE / 2; j++) {
            mlx_pixel_put(game->mlx, game->win, px + i, py + j, 0xFF0000); // Player is red
        }
    }
}

void draw_map(Game *game)
{
  for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH - 1; x++) {
            int color = (game->map[y][x] == 1) ? 0xFFFFFF : 0x000000; // Wall: white, Floor: black
            draw_square(game->mlx, game->win, x * TILE_SIZE, y * TILE_SIZE, color);
        }
    }
}


void print_map(int map[MAP_HEIGHT][MAP_WIDTH])
{
    size_t j = -1;
    size_t i = -1;

    while (++j < MAP_HEIGHT)
    {
        while (++i < MAP_WIDTH - 1) 
            printf("%d ", map[j][i]);
        i = -1;
        printf("\n");
    }
}


int key_hook(int keycode, Game *game) {
    // Clear window to redraw map
    mlx_clear_window(game->mlx, game->win);

    // Move player based on key press
    if (keycode == 13 && game->map[game->player_y - 1][game->player_x] == 0) // W (move up)
        game->player_y--;
    else if (keycode == 1 && game->map[game->player_y + 1][game->player_x] == 0) // S (move down)
        game->player_y++;
    else if (keycode == 0 && game->map[game->player_y][game->player_x - 1] == 0) // A (move left)
        game->player_x--;
    else if (keycode == 2 && game->map[game->player_y][game->player_x + 1] == 0) // D (move right)
        game->player_x++;

    // Redraw map and player
    draw_map(game);
    draw_player(game);
    return 0;
}

int main(int ac, char *av[])
{
    void    *mlx;        
    void    *win;
    Game    game;
    (void)ac;
    (void)av;

    mlx = mlx_init();
    if (!mlx)
    {
        write(2, "Error: Unable to initialize MinilibX\n", 37);
        return (1);
    }
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "2D Sphere in MLX");
    if (!win)
    {
        write(2, "Error: Unable to create window\n", 31);
        return (1);
    }
  
    // Vector3 sphere_center = {WIDTH / 2, HEIGHT / 2, 0};
    // int sphere_radius = 300;
    // Color sphere_color = {255, 77, 0}; // Red color
    // draw_sphere(mlx, win, sphere_center, sphere_radius, sphere_color);
    // Wait for events (close window with any key press)
    game.mlx = mlx;
    parse_map("./maps/good/map_only.cub", &game);
    print_map(game.map);

    mlx_key_hook(game.win, key_hook, &game);
    mlx_loop(mlx);
    return (0);
}