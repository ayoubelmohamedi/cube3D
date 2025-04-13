#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void draw_filled_circle(t_game *game, int radius, int color)
{
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius)
            {
                mlx_pixel_put(game->mlx, game->win, game->player_x + x, game->player_y + y, color);
            }
        }
    }
}

void parse_map(const char *filename, int map[MAX_HEIGHT][MAX_WIDTH], int *width, int *height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char line[MAX_WIDTH + 2]; // +2 for newline and null terminator
    int row = 0;

    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        printf("LINE\n");
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
            if (line[i] == '1' || line[i] == '0' || line[i] == 'S') {
                map[row][col++] = line[i] - '0'; // Convert char to int
            }
        }
        // Fill the rest of the row with null (0) to ensure it's properly terminated
        while (col < MAX_WIDTH) {
            map[row][col++] = 0;
        }
        row++;
    }
    *width = MAX_WIDTH;
    *height = row; // Set height to the number of rows read
    fclose(file);
}


void draw_square(void *mlx, void *win, int x, int y, int color) {
    printf("drawing a square\n");
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            mlx_pixel_put(mlx, win, x + i, y + j, color);
        }
    }
}

void draw_map(t_game *game)
{
    int color;
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            color = 0xFFFFFF; 
            if (game->map[y][x] == 1 || game->map[y][x] == 0)
            {
                color = (game->map[y][x] == 1) ? 0xFFFFFF : 0x000000; // Wall: white, Floor: black
                draw_square(game->mlx, game->win, x * TILE_SIZE, y * TILE_SIZE, color);
            }
            else
            {
                color = 0x00FF00; // green 
                int radius = 12;
                draw_filled_circle(game,radius,color);
                draw_square(game->mlx, game->win, x * TILE_SIZE, y * TILE_SIZE, color);
            }
        }
    }
}

// void render_scene(t_game *game)
// {
//     for (int x = 0; x < WIDTH; x++)
//     {
//         cast_ray(game, x);
//     }
//     mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
// }

// int	key_hook(int keycode, t_game *game);
// {
// 	printf("Hello from key_hook!\n");
// 	return (0);
// }

int main(int ac, char *av[])
{
    void    *mlx;        
    void    *win;
    void    *img;
    (void)ac;
    (void)av;

    int fplayer_x = 100;
    int fplayer_y = 160;
    int fov = 60;
    int dir = 90;
    // int distance_to_plane = 277;
    // int player_h = player_h / 2;
    // int player_speed = 16;
    // int plane_center_y = PROJ_PLANE_H / 2;
    // int fplayerMapX, fplayerMapY, fMiniMapWidth;

    // // movements flags
    // bool fKeyUp=false;
    // bool fKeyDown=false;
    // bool fKeyLeft=false;
    // bool fKeyRight=false;


    mlx = mlx_init();
    if (!mlx)
    {
        // (void*)write(2, "Error: Unable to initialize MinilibX\n", 37);
        return (1);
    }
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "2D Sphere in MLX");
    if (!win)
    {
        // (void*)write(2, "Error: Unable to create window\n", 31);
        return (1);
    }
    img = mlx_new_image(mlx,WIDTH, HEIGHT);
    if (!img)
    {
        mlx_destroy_window(mlx, win);
        return (1);
    }
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
        &game->line_length, &game->endian);

    // Vector3 sphere_center = {WIDTH / 2, HEIGHT / 2, 0};
    // int sphere_radius = 300;
    // Color sphere_color = {255, 77, 0}; // Red color
    // draw_sphere(mlx, win, sphere_center, sphere_radius, sphere_color);
    // Wait for events (close window with any key press)
    int map[MAX_HEIGHT][MAX_WIDTH];
    int width, height;
    parse_map("./maps/good/map_only.cub",map, &width, &height);
     
    t_game game = {map, fplayer_x, fplayer_y, fov, dir, mlx, win, NULL};
    size_t i = 0, j = 0;
    while (i < MAX_HEIGHT) {
        for (j = 0; j < MAX_WIDTH; j++) { 
            printf("%d ", map[i][j]);
        }
        printf("\n");
        i++;
    }

    draw_map(&game);
    mlx_loop(mlx);
    return (0);
}