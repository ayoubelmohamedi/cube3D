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
void parse_map(const char *filename, int map[MAP_HEIGHT][MAP_WIDTH], int *width, int *height) {
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
            if (line[i] == 'S' || line[i] == '1' || line[i] == '0')
                map[row][col++] = line[i] - 48;
        }
        col = 0;
        row++;
    }
    *width = MAP_WIDTH;
    *height = MAP_HEIGHT;
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
void draw_map(int map[MAP_HEIGHT][MAP_WIDTH], void *mlx, void *win)
{
  for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH - 1; x++) {
            int color = (map[y][x] == 1) ? 0xFFFFFF : 0x000000; // Wall: white, Floor: black
            draw_square(mlx, win, x * TILE_SIZE, y * TILE_SIZE, color);
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

int main(int ac, char *av[])
{
    void    *mlx;        
    void    *win;
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
    int map[MAP_HEIGHT][MAP_WIDTH];
    int width, height;
    parse_map("./maps/good/map_only.cub",map, &width, &height);
    print_map(map);
    draw_map(map, mlx, win);
    mlx_loop(mlx);
    return (0);
}